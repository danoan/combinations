#include <iostream>
#include <sstream>
#include <unistd.h>

#include "combinations/single-range/eager-recursive.h"
#include "combinations/single-range/lazy-recursive.h"
#include "combinations/single-range/lazy-nonrecursive.h"

#include "combinations/core/base/Range.hpp"
#include "combinations/core/single/Combinator.hpp"

#include "combinations/core/multithread/ThreadControl.h"
#include "combinations/core/multithread/ThreadInput.h"
#include "combinations/core/multithread/MultiThreadLC.h"

#include "combinations/utils/mockUtils.h"
#include "combinations/logger/logger.h"

typedef Combinations::Utils::IntVector IntVector;

#define QUERIES_PER_THREAD 10000

struct InputData
{
    uint numElems;
    uint elemsPerComb;
};

struct CombinationsResult
{
    CombinationsResult(const std::string &executionTime, uint totalCombs) : executionTime(executionTime),
                                                                                    totalCombs(totalCombs) {}

    std::string executionTime;
    uint totalCombs;
};

void usage(int argc, char* argv[])
{
    std::cerr << "Usage: " << argv[0] << "numElems elemsPerComb" << std::endl;
}

InputData readInput(int argc, char* argv[])
{
    InputData id;
    if(argc<3)
    {
        usage(argc,argv);
        exit(1);
    }

    id.numElems = std::stoul( argv[optind++] );
    id.elemsPerComb = std::stoul( argv[optind++] );

    return id;
}

CombinationsResult eagerRecursive(const InputData& id)
{
    auto intV = Combinations::Utils::createIntegerVector(id.numElems);

    std::stringstream ss;
    Combinations::Logger logger(ss,false);
    logger.startTimer();
    auto combs = Combinations::EagerRecursive::combinations<int>(id.elemsPerComb,intV.begin(),intV.end());
    logger.endTimer();

    return CombinationsResult(ss.str(),combs.size());
}

CombinationsResult lazyRecursive(const InputData& id)
{
    auto intV = Combinations::Utils::createIntegerVector(id.numElems);
    auto combinator = Combinations::LazyRecursive::combinations(id.elemsPerComb,intV.begin(),intV.end());
    IntVector nextComb;

    std::stringstream ss;
    Combinations::Logger logger(ss,false);
    logger.startTimer();
    uint totalCombs=0;
    while(combinator.next(nextComb)){++totalCombs;}
    logger.endTimer();

    return CombinationsResult(ss.str(),totalCombs);
}

CombinationsResult lazyNonRecursive(const InputData& id)
{
    auto intV = Combinations::Utils::createIntegerVector(id.numElems);
    auto combinator = Combinations::LazyNonRecursive::combinations(id.elemsPerComb,intV.begin(),intV.end());
    IntVector nextComb;

    std::stringstream ss;
    Combinations::Logger logger(ss,false);
    logger.startTimer();
    uint totalCombs=0;
    while(combinator.next(nextComb)){++totalCombs;}
    logger.endTimer();

    return CombinationsResult(ss.str(),totalCombs);
}


CombinationsResult lazyGeneric(const InputData& id)
{
    auto intV = Combinations::Utils::createIntegerVector(id.numElems);


    auto range = Combinations::Core::addRange(intV.begin(),intV.end(),id.elemsPerComb);
    auto combinator = Combinations::Core::Single::createCombinator(range);
    auto resolver = combinator.resolver();

    std::stringstream ss;
    Combinations::Logger logger(ss,false);
    logger.startTimer();
    int totalCombs=0;
    while( combinator.next(resolver) ) ++totalCombs;
    logger.endTimer();

    return CombinationsResult(ss.str(),totalCombs);
}

CombinationsResult multithreadLazyGeneric(const InputData& id)
{
    auto intV = Combinations::Utils::createIntegerVector(id.numElems);


    auto range = Combinations::Core::addRange(intV.begin(),intV.end(),id.elemsPerComb);
    auto combinator = Combinations::Core::Single::createCombinator(range);
    auto resolver = combinator.resolver();

    struct Params{};
    struct UserVars{ UserVars():totalCombs(0){} void restart(){}; uint totalCombs; };

    typedef Combinations::Core::MultiThread::ThreadInput<decltype(combinator),UserVars,Params> MyThreadInput;
    typedef Combinations::Core::MultiThread::Controller<MyThreadInput> MyController;
    typedef MyController::MyResolver MyResolver;
    typedef Combinations::Core::MultiThread::ThreadControl ThreadControl;

    uint totalCombs=0;
    MyController::CallbackFunction cbf = [](MyResolver& r, MyThreadInput& ti, ThreadControl& tc) mutable{++ti.vars.totalCombs;};

    Params params;
    MyController mtController(std::thread::hardware_concurrency(),QUERIES_PER_THREAD,cbf);


    std::stringstream ss;
    Combinations::Logger logger(ss,false);
    logger.startTimer();

    mtController.start(combinator,params);
    logger.endTimer();

    for(auto it=mtController.threadInputVector.begin();it!=mtController.threadInputVector.end();++it)
    {
        totalCombs+=it->vars.totalCombs;
    }

    return CombinationsResult(ss.str(),totalCombs);
}

void printResults(CombinationsResult cr,const std::string& title)
{
    std::cout << "#" << title << "\n\n";
    std::cout << "Total Combinations: " << cr.totalCombs << "\n";
    std::cout << "Execution Time: " << cr.executionTime << "\n";
    std::cout << "----------------------\n";
}

int main(int argc, char* argv[])
{
    InputData id = readInput(argc,argv);

    std::cout << "*******Comparison Results*******\n\n";

    printResults(eagerRecursive(id),"Eager Recursive");
    printResults(lazyRecursive(id),"Lazy Recursive");
    printResults(lazyNonRecursive(id),"Lazy NonRecursive");
    printResults(lazyGeneric(id),"Lazy Generic");
    printResults(multithreadLazyGeneric(id),"Lazy Generic Multithread");


    return 0;
}