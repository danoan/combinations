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


struct UserVars
{
    void restart(){};
    std::vector<IntVector> cv;
};

struct Params{};


int main(int argc, char* argv[])
{
    unsigned int numThreads = 4;
    unsigned int queriesPerThread = 10;

    IntVector v1 = {1,2,3};
    IntVector v2 = {4,5,6};
    IntVector v3 = {7,8,9,10};

    auto range = addRange(v1.begin(),v1.end(),2)
            .addRange(v2.begin(),v2.end(),2)
            .addRange(v3.begin(),v3.end(),2);

    auto mrc = Multiple::createCombinator(range);

    typedef decltype(mrc) MyCombinator;
    typedef MyCombinator::MyResolver MyResolver;

    typedef MultiThread::ThreadInput<MyCombinator,UserVars,Params> MyThreadInput;
    typedef MultiThread::Controller<MyThreadInput> MyThreadController;
    typedef MultiThread::ThreadControl ThreadControl;


    MyThreadController::CallbackFunction cbf = [](MyResolver& resolver,MyThreadInput& ti, ThreadControl& tc) mutable
    {
        IntVector c1(2),c2(2),c3(2),unionV;
        resolver >> c3 >> c2 >> c1;

        unionV.insert(unionV.end(),c1.begin(),c1.end());
        unionV.insert(unionV.end(),c2.begin(),c2.end());
        unionV.insert(unionV.end(),c3.begin(),c3.end());

        ti.vars.cv.push_back(unionV);
    };

    Params params;
    MyThreadController mtController(numThreads,queriesPerThread,cbf);
    mtController.start(mrc,params);


    int totalCombs=0;
    for(unsigned int i=0;i<numThreads;++i)
    {
        const std::vector<IntVector>& cv = mtController.threadInputVector[i].vars.cv;
        totalCombs+=cv.size();
        Utils::printCombinations(cv.begin(),cv.end());
    }


    std::cout << "\n" << totalCombs << " combinations!\n\n";

    return 0;
}