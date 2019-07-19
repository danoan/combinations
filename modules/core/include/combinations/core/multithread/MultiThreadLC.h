#ifndef LAZY_COMBINATOR_MULTITHREADLC_H
#define LAZY_COMBINATOR_MULTITHREADLC_H

#include <stdexcept>
#include <cmath>
#include <functional>

#include <stack>
#include <vector>

#include <thread>
#include <mutex>
#include <condition_variable>

#include "ThreadInput.h"
#include "ThreadControl.h"

namespace Combinations
{
    namespace Core
    {
        namespace MultiThread
        {
            template<class TThreadInput>
            class Controller
            {
            public:
                typedef Controller<TThreadInput> Self;

                typedef TThreadInput MyThreadInput;
                typedef typename MyThreadInput::MyResolver MyResolver;
                typedef typename MyThreadInput::Params Params;
                typedef typename MyThreadInput::MyCombinator MyCombinator;


                typedef std::function<void(MyResolver&, MyThreadInput&, ThreadControl&)> CallbackFunction;

            private:
                typedef unsigned int uint;

            public:
                Controller( uint numThreads,
                            uint queriesPerThread,
                            CallbackFunction cbf):  numThreads(numThreads),
                                                    queriesPerThread(queriesPerThread),
                                                    cbf(cbf)
                {
                    this->threads.resize(numThreads);
                    this->LCVector.resize(numThreads);

                    for(uint i=0;i<numThreads;++i)
                    {
                        this->threadPool.push(i);
                    }
                }

                void threadStart(MyThreadInput& ti, ThreadControl tc )
                {
                    ti.restart();

                    auto resolver = ti.combinatorPt->resolver();
                    int q=0;
                    while(  ti.combinatorPt->next(resolver) &&
                            q<tc.maxQueries &&
                            tc.state==ThreadControl::RUNNING )
                    {
                        this->cbf(resolver,ti,tc);
                        ++q;
                    }

                    this->threadEnd(tc);
                }

                void threadEnd(const ThreadControl& tc)
                {
                    std::unique_lock<std::mutex> lockNotify(this->mutexPoolStack);

                    this->threadPool.push(tc.vectorPos);
                    this->cvPoolStack.notify_one();
                }

                void start(MyCombinator& combinatorModel,const Params& params)
                {
                    MyResolver mockValue = combinatorModel.resolver();


                    for(uint i=0;i<numThreads;++i)
                    {
                        this->LCVector[i] = new MyCombinator(combinatorModel);
                        threadInputVector.push_back( MyThreadInput(LCVector[i], params) );
                    }

                    bool existsNext=true;
                    do
                    {
                        std::unique_lock<std::mutex> lockNotify(this->mutexPoolStack);

                        {
                            while (!this->threadPool.empty())
                            {
                                int tPos = threadPool.top();
                                threadPool.pop();

                                delete LCVector[tPos];
                                LCVector[tPos] = new MyCombinator(combinatorModel);


                                threadInputVector[tPos].combinatorPt = LCVector[tPos];
                                threads[tPos] = std::thread(&Self::threadStart,
                                                            this,
                                                            std::ref(threadInputVector[tPos]),
                                                            ThreadControl(tPos, queriesPerThread));
                                threads[tPos].detach();

                                for (uint currSize = 0; currSize < queriesPerThread; ++currSize) {
                                    existsNext = combinatorModel.next(mockValue);
                                    if (!existsNext) break;
                                }
                                if (!existsNext) break;
                            }
                        }
                        cvPoolStack.wait(lockNotify);
                    }while(existsNext);

                    std::unique_lock<std::mutex> lockNotify(this->mutexPoolStack);
                    while(this->threadPool.size()!=numThreads)
                    {
                        cvPoolStack.wait(lockNotify);
                    }

                }

                ~Controller(){}

            public:
                uint numThreads;
                uint queriesPerThread;

                std::vector<std::thread> threads;
                std::vector<MyThreadInput> threadInputVector;

                std::stack<int> threadPool;
                std::vector<MyCombinator*> LCVector;

                CallbackFunction cbf;

                std::mutex mutexPoolStack;
                std::condition_variable cvPoolStack;


            };
        }
    }
}

#endif //LAZY_COMBINATOR_MULTITHREADLC_H
