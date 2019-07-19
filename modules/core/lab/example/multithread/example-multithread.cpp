#include "combinations/core/base/Range.hpp"
#include "combinations/core/multiple/Combinator.h"
#include "combinations/core/single/Combinator.hpp"

#include "combinations/utils/displayUtils.h"
#include "combinations/utils/mockUtils.h"

#include "combinations/core/multithread/MultiThreadLC.h"
#include "combinations/core/multithread/ThreadInput.h"
#include "combinations/logger/logger.h"

using namespace Combinations;
using namespace Combinations::Core;

typedef std::vector<int> IntVector;


struct ControlVars
{
    void restart(){};
    std::vector<IntVector> cv;
};

struct Params{};

void multipleRangeExample()
{
    IntVector v1 = {1,2,3};
    IntVector v2 = {4,5,6};
    IntVector v3 = {7,8,9,10};

    auto range = addRange(v1.begin(),v1.end(),2)
            .addRange(v2.begin(),v2.end(),2)
            .addRange(v3.begin(),v3.end(),2);

    auto mrc = Multiple::createCombinator(range);

    typedef decltype(mrc) MyCombinator;
    typedef MyCombinator::MyResolver MyResolver;

    typedef MultiThread::ThreadInput<MyCombinator,ControlVars,Params> MyThreadInput;
    typedef MultiThread::Controller<MyThreadInput,4> MyThreadController;
    typedef MultiThread::ThreadControl ThreadControl;

    std::vector<IntVector> cv;
    std::mutex cvMutex;

    MyThreadController::CallbackFunction cbf = [&cv,&cvMutex](MyResolver& resolver,MyThreadInput& ti, ThreadControl& tc) mutable
    {
        IntVector c1(2),c2(2),c3(2),unionV;
        resolver >> c3 >> c2 >> c1;

        unionV.insert(unionV.end(),c1.begin(),c1.end());
        unionV.insert(unionV.end(),c2.begin(),c2.end());
        unionV.insert(unionV.end(),c3.begin(),c3.end());

        {
            std::lock_guard<std::mutex> lockCV(cvMutex);
            cv.push_back(unionV);
        }


        unionV.clear();
    };

    Params params;
    MyThreadController mtController(10,cbf);

    std::stringstream ss;
    Logger logger(ss,false);
    logger.startTimer();
    mtController.start(mrc,params);
    logger.endTimer();

    Utils::printCombinations(cv.begin(),cv.end());
    std::cout << "\n" << cv.size() << " combinations!\n\n";


    std::cout << ss.str() << std::endl;
}

void highLoadExample(int n,int k)
{
    constexpr int numThreads = 4;
    IntVector v = Utils::createIntegerVector(n);
    long int totalComb = 1;
    for(int i=0;i<k;++i) totalComb*=(n-i);
    for(int i=1;i<=k;++i) totalComb/=i;
    int threadSize = (int) std::ceil( totalComb/(1.0*numThreads) );


    auto range = addRange(v.begin(),v.end(),k);
    auto mrc = Single::createCombinator(range);

    typedef decltype(mrc) MyCombinator;
    typedef MyCombinator::MyResolver MyResolver;

    typedef MultiThread::ThreadInput<MyCombinator,ControlVars,Params> MyThreadInput;
    typedef MultiThread::Controller<MyThreadInput,numThreads> MyThreadController;
    typedef MultiThread::ThreadControl ThreadControl;


    std::mutex cvMutex;

    MyThreadController::CallbackFunction cbf = [&cvMutex,&k](MyResolver& resolver,MyThreadInput& ti, ThreadControl& tc) mutable
    {
        IntVector c1(k),unionV;
        resolver >> c1;

        unionV.insert(unionV.end(),c1.begin(),c1.end());

        ti.vars.cv.push_back(unionV);
    };

    Params params;
    MyThreadController mtController(threadSize,cbf);

    std::stringstream ss;
    Logger logger(ss,false);
    logger.startTimer();
    mtController.start(mrc,params);
    logger.endTimer();


    long int visitedElems=0;
    for(int i=0;i<numThreads;++i)
    {
        visitedElems+=mtController.threadInputVector[i].vars.cv.size();
    }

    //Utils::printCombinations(cv.begin(),cv.end());
    std::cout << "Expected Combinations: " << totalComb << "\n";
    std::cout << "Computed Combinations: " << visitedElems << "\n\n";


    std::cout << "Elements per thread: " << threadSize << std::endl;
    std::cout << "Execution Time: " << ss.str() << std::endl;

}

int main(int argc, char* argv[])
{
    //simpleExample();
    highLoadExample(50,6);

    return 0;
}