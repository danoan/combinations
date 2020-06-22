#include "magLac/lab/test/core/multithread/correcteness.h"

namespace magLac
{
    namespace Test
    {
        namespace Multithread
        {
            bool belongsTo(const std::set<int>& currComb,const CombinationsContainer& combs)
            {
                for(auto itU=combs.cbegin();itU!=combs.cend();++itU)
                {
                    bool found = true;
                    for(auto it=itU->cbegin();it!=itU->cend();++it)
                    {
                        if(currComb.find(*it)==currComb.end())
                        {
                            found=false;
                            break;
                        }
                    }

                    if(found) return true;
                }

                return false;
            }

            bool correctenessMultithread(Logger& logger, Size numThreads, Size n, Size k, const CombinationsCheckContainer& checkV)
            {
                logger << Logger::HeaderTwo << "TestCorrecteness" << Logger::Normal;
                logger << "Num Threads: " << numThreads << "\n"
                       << "Num. Elems: " << n << "\n"
                       << "Elems. per comb.: " << k << "\n";

                IntVector v = Utils::createIntegerVector(n);
                Size totalComb = 1;

                for(Size i=0;i<k;++i) totalComb*=(n-i);
                for(Size i=1;i<=k;++i) totalComb/=i;
                Size queriesPerThread = (Size) std::ceil( totalComb/(1.0*numThreads) );

                auto range = magLac::Core::addRange(v.begin(),v.end(),k);
                auto mrc = magLac::Core::createCombinator(range);

                typedef decltype(mrc) MyCombinator;
                typedef MyCombinator::MyResolver MyResolver;

                typedef magLac::Core::MultiThread::ThreadInput<MyCombinator,CorrectUserVars,CorrectParams> MyThreadInput;
                typedef magLac::Core::MultiThread::Trigger<MyThreadInput> MyThreadTrigger;
                typedef magLac::Core::MultiThread::ThreadControl ThreadControl;


                IntVector c1(k);
                MyThreadTrigger::CallbackFunction cbf = [&c1](MyResolver& resolver,MyThreadInput& ti, ThreadControl& tc) mutable
                {
                    resolver >> c1;
                    ti.vars.cv.push_back(c1);
                    c1.clear();
                };

                CorrectParams params;
                MyThreadTrigger mtTrigger(numThreads,queriesPerThread,cbf);

                mtTrigger.start(mrc,params);

                CombinationsContainer combinations;
                Size visitedElems=0;
                for(Size i=0;i<numThreads;++i)
                {
                    const CombinationsContainer& cc = mtTrigger.threadInputVector[i].vars.cv;
                    visitedElems+=cc.size();

                    combinations.insert(combinations.end(),cc.begin(),cc.end());
                }

                logger << "Expected Combinations: " << totalComb << "\n";
                logger << "Computed Combinations: "  << visitedElems << "\n\n";


                for(auto it=checkV.begin();it!=checkV.end();++it)
                {
                    if(!belongsTo(*it,combinations))
                    {
                        logger << "Passed: false\n";

                        logger << "Computed: \n";
                        Utils::printCombinations(combinations.begin(),combinations.end(),logger.stream());

                        logger << "Expected: \n";
                        Utils::printCombinations(checkV.begin(),checkV.end(),logger.stream());

                        return false;
                    }
                }

                logger << "Passed: true\n";


                return totalComb==visitedElems;
            }

            bool correcteness(Logger& logger)
            {
                bool flag = true;
                const CombinationsCheckContainer checkV = { {1,2,3},{1,2,4},{1,2,5},{1,2,6},
                                                            {1,3,4},{1,3,5},{1,3,6},
                                                            {1,4,5},{1,4,6},
                                                            {1,5,6},
                                                            {2,3,4},{2,3,5},{2,3,6},
                                                            {2,4,5},{2,4,6},
                                                            {2,5,6},
                                                            {3,4,5},{3,4,6},
                                                            {3,5,6},
                                                            {4,5,6}};

                flag = flag && correctenessMultithread(logger,1,6,3,checkV);
                flag = flag && correctenessMultithread(logger,2,6,3,checkV);
                flag = flag && correctenessMultithread(logger,3,6,3,checkV);
                flag = flag && correctenessMultithread(logger,4,6,3,checkV);

                return flag;
            }
        }
    }
}