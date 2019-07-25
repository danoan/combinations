#include "execution.h"

namespace magLac
{
    namespace Test
    {
        bool executionMultithread(Logger& logger, Size numThreads, Size n, Size k)
        {
            logger << Logger::HeaderTwo << "TestExecution" << Logger::Normal;
            logger << "Num Threads:  " << numThreads << "\n"
            << "Num. Elems:  " << n << "\n"
            << "Elems. per comb.: " << k << "\n";

            bool flag=true;
            logger.startTimer();
            try
            {
                IntVector v = Utils::createIntegerVector(n);
                Size totalComb = 1;

                for(Size i=0;i<k;++i) totalComb*=(n-i);
                for(Size i=1;i<=k;++i) totalComb/=i;
                Size queriesPerThread = (Size) std::ceil( totalComb/(1.0*numThreads) );

                auto range = magLac::Core::addRange(v.begin(),v.end(),k);
                auto mrc = magLac::Core::Single::createCombinator(range);

                typedef decltype(mrc) MyCombinator;
                typedef MyCombinator::MyResolver MyResolver;

                typedef magLac::Core::MultiThread::ThreadInput<MyCombinator,ExecutionUserVars,ExecutionParams> MyThreadInput;
                typedef magLac::Core::MultiThread::Controller<MyThreadInput> MyThreadController;
                typedef magLac::Core::MultiThread::ThreadControl ThreadControl;


                IntVector c1(k);
                MyThreadController::CallbackFunction cbf = [&c1](MyResolver& resolver,MyThreadInput& ti, ThreadControl& tc) mutable
                {
                    resolver >> c1;
                    ti.vars.cv.push_back(c1);
                };

                ExecutionParams params;
                MyThreadController mtController(numThreads,queriesPerThread,cbf);

                logger.startTimer();
                mtController.start(mrc,params);
                logger << "Execution time: ";
                logger.endTimer();

                Size visitedElems=0;
                for(Size i=0;i<numThreads;++i)
                {
                    visitedElems+=mtController.threadInputVector[i].vars.cv.size();
                }

                logger << "Expected Combinations: " << totalComb << "\n";
                logger << "Computed Combinations: "  << visitedElems << "\n\n";
            }
            catch(std::exception& ex)
            {
                logger << "Error: " << ex.what();
                flag=false;
            }
            logger.endTimer();

            logger << "Passed: " << flag;
            return flag;
        }

        bool execution(Logger& logger)
        {
            bool flag = true;
            flag = flag && executionMultithread(logger,2,20,4);
            flag = flag && executionMultithread(logger,4,20,4);
            flag = flag && executionMultithread(logger,8,20,4);
            flag = flag && executionMultithread(logger,16,20,4);

            flag = flag && executionMultithread(logger,2,50,5);
            flag = flag && executionMultithread(logger,4,50,5);
            flag = flag && executionMultithread(logger,8,50,5);
            flag = flag && executionMultithread(logger,16,50,5);

            return flag;
        }
    }
}