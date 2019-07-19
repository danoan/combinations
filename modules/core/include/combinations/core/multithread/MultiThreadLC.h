#ifndef LAZY_COMBINATOR_MULTITHREADLC_H
#define LAZY_COMBINATOR_MULTITHREADLC_H

#include <stdexcept>
#include <cmath>
#include <functional>

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
            template<class TThreadInput,int ThreadPoolSize=4>
            class Controller
            {
            public:
                typedef Controller<TThreadInput,ThreadPoolSize> Self;

                typedef TThreadInput MyThreadInput;
                typedef typename MyThreadInput::MyResolver MyResolver;
                typedef typename MyThreadInput::Params Params;
                typedef typename MyThreadInput::MyCombinator MyCombinator;


                typedef std::function<void(MyResolver&, MyThreadInput&, ThreadControl&)> CallbackFunction;


            public:
                Controller(int threadSize,CallbackFunction cbf):threadSize(threadSize),cbf(cbf)
                {
                    for(int i=0;i<ThreadPoolSize;++i)
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


                    for(int i=0;i<ThreadPoolSize;++i)
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
                                                            ThreadControl(tPos, threadSize));
                                threads[tPos].detach();

                                for (int currSize = 0; currSize < threadSize; ++currSize) {
                                    existsNext = combinatorModel.next(mockValue);
                                    if (!existsNext) break;
                                }
                                if (!existsNext) break;
                            }
                        }

                        cvPoolStack.wait(lockNotify);
                    }while(existsNext);

                    std::unique_lock<std::mutex> lockNotify(this->mutexPoolStack);
                    while(this->threadPool.size()!=ThreadPoolSize)
                    {
                        cvPoolStack.wait(lockNotify);
                    }

                }

                ~Controller(){}

            public:
                int threadSize;

                std::thread threads[ThreadPoolSize];
                std::vector<MyThreadInput> threadInputVector;

                std::stack<int> threadPool;
                MyCombinator* LCVector[ThreadPoolSize];

                CallbackFunction cbf;

                std::mutex mutexPoolStack;
                std::condition_variable cvPoolStack;


            };
        }
    }
}

#endif //LAZY_COMBINATOR_MULTITHREADLC_H
