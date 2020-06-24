#include <iostream>
#include <sstream>
#include <unistd.h>

#include "eager-recursive.h"
#include "lazy-recursive.h"
#include "lazy-nonrecursive.h"

#include "magLac/magLac.h"
#include "magLac/multithread.h"

#include "magLac/lab/utils/mockUtils.h"
#include "magLac/lab/logger/logger.h"

typedef magLac::Utils::IntVector IntVector;

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
    auto intV = magLac::Utils::createIntegerVector(id.numElems);

    std::stringstream ss;
    magLac::Logger logger(ss,false);
    logger.startTimer();
    auto combs = magLac::EagerRecursive::combinations<int>(id.elemsPerComb,intV.begin(),intV.end());
    logger.endTimer();

    return CombinationsResult(ss.str(),combs.size());
}

CombinationsResult lazyRecursive(const InputData& id)
{
    auto intV = magLac::Utils::createIntegerVector(id.numElems);
    auto combinator = magLac::LazyRecursive::combinations(id.elemsPerComb,intV.begin(),intV.end());
    IntVector nextComb;

    std::stringstream ss;
    magLac::Logger logger(ss,false);
    logger.startTimer();
    uint totalCombs=0;
    while(combinator.next(nextComb)){++totalCombs;}
    logger.endTimer();

    return CombinationsResult(ss.str(),totalCombs);
}

CombinationsResult lazyNonRecursive(const InputData& id)
{
    auto intV = magLac::Utils::createIntegerVector(id.numElems);
    auto combinator = magLac::LazyNonRecursive::combinations(id.elemsPerComb,intV.begin(),intV.end());
    IntVector nextComb;

    std::stringstream ss;
    magLac::Logger logger(ss,false);
    logger.startTimer();
    uint totalCombs=0;
    while(combinator.next(nextComb)){++totalCombs;}
    logger.endTimer();

    return CombinationsResult(ss.str(),totalCombs);
}


CombinationsResult lazyGeneric(const InputData& id)
{
    auto intV = magLac::Utils::createIntegerVector(id.numElems);


    auto range = magLac::Core::addRange(intV.begin(),intV.end(),id.elemsPerComb);
    auto combinator = magLac::Core::createCombinator(range);
    auto resolver = combinator.resolver();

    std::stringstream ss;
    magLac::Logger logger(ss,false);
    logger.startTimer();
    int totalCombs=0;
    while( combinator.next(resolver) ) ++totalCombs;
    logger.endTimer();

    return CombinationsResult(ss.str(),totalCombs);
}

CombinationsResult multithreadLazyGeneric(const InputData& id)
{
    auto intV = magLac::Utils::createIntegerVector(id.numElems);


    auto range = magLac::Core::addRange(intV.begin(),intV.end(),id.elemsPerComb);
    auto combinator = magLac::Core::createCombinator(range);

    struct MyThreadData
    {
        struct MutableData
        {
            MutableData():totalCombs(0){}
            void restart(){};
            uint totalCombs;
        };

        struct ConstantData{};

        MutableData mutableData;
        ConstantData constantData;
    };

    MyThreadData data;
    auto planner = magLac::slice(combinator,data,std::thread::hardware_concurrency(),QUERIES_PER_THREAD);
    typedef decltype(planner)::MyThreadInfo MyThreadInfo;


    std::stringstream ss;
    magLac::Logger logger(ss,false);
    logger.startTimer();

    uint totalCombs=0;
    planner.run( [](MyThreadInfo&& ti) mutable{
        ++ti.data.mutableData.totalCombs;
    });

    logger.endTimer();

    for(auto data:planner)
    {
        totalCombs+=data.mutableData.totalCombs;
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