#ifndef MAGLAC_MULTITHREAD_H
#define MAGLAC_MULTITHREAD_H

#include "magLac/core/multithread/Trigger.h"
#include "magLac/core/multithread/DataChunk.h"
#include "magLac/core/multithread/ThreadInfo.h"

namespace magLac
{
    namespace Private
    {
        template<class TThreadData,class TCombinator>
        class _ThreadWrapper
        {
        public:
            typedef Core::MultiThread::DataChunk<TCombinator,TThreadData> MyDataChunk;
            typedef typename MyDataChunk::ConstantData ConstantData;
            typedef Core::MultiThread::Trigger<MyDataChunk> MyThreadTrigger;
            typedef typename MyThreadTrigger::MyThreadInfo MyThreadInfo;

            typedef std::vector<MyDataChunk> ThreadDataVector;
            typedef typename ThreadDataVector::const_iterator ThreadDataVectorIterator;

            typedef typename MyThreadTrigger::CallbackFunction CallbackFunction;

            _ThreadWrapper(TCombinator& combinator,
                    const ConstantData& constantData,
                    size_t numThreads,
                    size_t queriesPerThread)
            :combinator(combinator),
             constantData(constantData),
            trigger(numThreads,queriesPerThread)
            {}

            void run(CallbackFunction cbf)
            {
                trigger.start(combinator,constantData,cbf);
            }

            ThreadDataVectorIterator begin()
            {
                return trigger.threadDataVector.begin();
            }

            ThreadDataVectorIterator end()
            {
                return trigger.threadDataVector.end();
            }


        private:
            TCombinator& combinator;
            const ConstantData& constantData;
            MyThreadTrigger trigger;
        };
    }

    template<class TThreadData,class TCombinator>
    Private::_ThreadWrapper<TThreadData,TCombinator> slice(TCombinator &combinator,
                                                           TThreadData &threadData,
                                                           size_t numThreads = std::thread::hardware_concurrency(),
                                                           size_t queriesPerThread = 1e5)
    {
        return Private::_ThreadWrapper<TThreadData,TCombinator>(combinator,threadData.constantData,numThreads,queriesPerThread);
    }
}



#endif //MAGLAC_MULTITHREAD_H
