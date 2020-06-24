#ifndef MAGLAC_CORE_MULTITHREAD_TRIGGER_H
#define MAGLAC_CORE_MULTITHREAD_TRIGGER_H

#include <stdexcept>
#include <cmath>
#include <functional>

#include <stack>
#include <vector>

#include <thread>
#include <mutex>
#include <condition_variable>

#include "DataChunk.h"
#include "ThreadControl.h"
#include "ThreadInfo.h"

namespace magLac
{
    namespace Core
    {
        namespace MultiThread
        {
            template<class TDataChunk>
            class Trigger
            {
            public:
                typedef Trigger<TDataChunk> Self;

                typedef TDataChunk MyDataChunk;
                typedef typename MyDataChunk::MyResolver MyResolver;
                typedef typename MyDataChunk::ConstantData ConstantData;
                typedef typename MyDataChunk::MyCombinator MyCombinator;
                typedef ThreadInfo<MyDataChunk> MyThreadInfo;


                typedef std::function<void(MyThreadInfo&&)> CallbackFunction;

            private:
                typedef unsigned int uint;

            public:
                Trigger( uint numThreads,
                         uint queriesPerThread)
                        :  numThreads(numThreads),
                           queriesPerThread(queriesPerThread)
                {
                    this->threads.resize(numThreads);
                    this->LCVector.resize(numThreads);

                    for(uint i=0;i<numThreads;++i)
                    {
                        this->threadPool.push(i);
                    }
                }

                void threadStart(MyDataChunk& dc, ThreadControl tc, CallbackFunction cbf )
                {
                    dc.restart();

                    auto resolver = dc.combinatorPt->resolver();
                    int q=0;
                    while(  dc.combinatorPt->next(resolver) &&
                            q<tc.maxQueries &&
                            tc.state==ThreadControl::RUNNING )
                    {
                        cbf( MyThreadInfo(resolver,dc,tc) );
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

                void start(MyCombinator& combinatorModel,const ConstantData& constantData, CallbackFunction cbf)
                {
                    MyResolver mockValue = combinatorModel.resolver();


                    for(uint i=0;i<numThreads;++i)
                    {
                        this->LCVector[i] = new MyCombinator(combinatorModel);
                        threadDataVector.push_back( MyDataChunk(LCVector[i], constantData) );
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


                                threadDataVector[tPos].combinatorPt = LCVector[tPos];
                                threads[tPos] = std::thread(&Self::threadStart,
                                                            this,
                                                            std::ref(threadDataVector[tPos]),
                                                            ThreadControl(tPos, queriesPerThread),
                                                            cbf);
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

                    bool childRunning=true;
                    while(childRunning)
                    {
                        std::unique_lock<std::mutex> lockNotify(this->mutexPoolStack);
                        if(this->threadPool.size()!=numThreads)
                        {
                            cvPoolStack.wait(lockNotify);
                        }else
                        {
                            childRunning=false;
                        }
                    }

                }

                ~Trigger()
                {
                    for(auto v:LCVector) delete v;
                }

            public:
                uint numThreads;
                uint queriesPerThread;

                std::vector<std::thread> threads;
                std::vector<MyDataChunk> threadDataVector;

                std::stack<int> threadPool;
                std::vector<MyCombinator*> LCVector;

                std::mutex mutexPoolStack;
                std::condition_variable cvPoolStack;


            };
        }
    }
}

#endif //MAGLAC_CORE_MULTITHREAD_TRIGGER_H

