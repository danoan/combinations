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

namespace magLac {
namespace Core {
namespace MultiThread {
template<class TDataChunk>
class Trigger {
 private:
  typedef Trigger<TDataChunk> Self;

  typedef TDataChunk MyDataChunk;
  typedef typename MyDataChunk::MyResolver MyResolver;
  typedef std::vector<MyDataChunk> ThreadDataVector;

 public:
  typedef ThreadInfo<MyDataChunk> MyThreadInfo;
  typedef typename ThreadDataVector::const_iterator ThreadDataVectorIterator;

  typedef typename MyDataChunk::ConstantData ConstantData;
  typedef typename MyDataChunk::MyCombinator MyCombinator;
  typedef std::function<void(MyThreadInfo &&)> CallbackFunction;


 public:
  Trigger(size_t numThreads,
          size_t queriesPerThread)
      : m_numThreads(numThreads),
        m_queriesPerThread(queriesPerThread) {
    this->m_threads.resize(numThreads);
    this->m_LCVector.resize(numThreads);

    for (size_t i = 0; i < numThreads; ++i) {
      this->m_threadPool.push(i);
    }
  }

  ~Trigger() {
    for (auto v:m_LCVector) delete v;
  }
  
  ThreadDataVectorIterator begin() const{ return m_threadDataVector.begin(); }
  ThreadDataVectorIterator end() const{ return m_threadDataVector.end(); }

  void start(MyCombinator &combinatorModel, const ConstantData &constantData, CallbackFunction cbf) {
    MyResolver mockValue = combinatorModel.resolver();

    for (size_t i = 0; i < m_numThreads; ++i) {
      this->m_LCVector[i] = new MyCombinator(combinatorModel);
      m_threadDataVector.push_back(MyDataChunk(m_LCVector[i], constantData));
    }

    bool existsNext = true;
    do {
      std::unique_lock<std::mutex> lockNotify(this->m_mutexPoolStack);

      {
        while (!this->m_threadPool.empty()) {
          int tPos = m_threadPool.top();
          m_threadPool.pop();

          delete m_LCVector[tPos];
          m_LCVector[tPos] = new MyCombinator(combinatorModel);

          m_threadDataVector[tPos].combinatorPt = m_LCVector[tPos];
          m_threads[tPos] = std::thread(&Self::threadStart,
                                      this,
                                      std::ref(m_threadDataVector[tPos]),
                                      ThreadControl(tPos, m_queriesPerThread),
                                      cbf);
          m_threads[tPos].detach();

          for (size_t currSize = 0; currSize < m_queriesPerThread; ++currSize) {
            existsNext = combinatorModel.next(mockValue);
            if (!existsNext) break;
          }
          if (!existsNext) break;
        }
      }
      m_cvPoolStack.wait(lockNotify);
    } while (existsNext);

    bool childRunning = true;
    while (childRunning) {
      std::unique_lock<std::mutex> lockNotify(this->m_mutexPoolStack);
      if (this->m_threadPool.size() != m_numThreads) {
        m_cvPoolStack.wait(lockNotify);
      } else {
        childRunning = false;
      }
    }

  }
  
 private:

  void threadStart(MyDataChunk &dc, ThreadControl tc, CallbackFunction cbf) {
    dc.restart();

    auto resolver = dc.combinatorPt->resolver();
    int q = 0;
    while (dc.combinatorPt->next(resolver) &&
        q < tc.maxQueries &&
        tc.state == ThreadControl::RUNNING) {
      cbf(MyThreadInfo(resolver, dc, tc));
      ++q;
    }

    this->threadEnd(tc);
  }

  void threadEnd(const ThreadControl &tc) {
    std::unique_lock<std::mutex> lockNotify(this->m_mutexPoolStack);

    this->m_threadPool.push(tc.vectorPos);
    this->m_cvPoolStack.notify_one();
  }
  

 private:
  size_t m_numThreads;
  size_t m_queriesPerThread;

  std::vector<std::thread> m_threads;
  ThreadDataVector m_threadDataVector;

  std::stack<int> m_threadPool;
  std::vector<MyCombinator *> m_LCVector;

  std::mutex m_mutexPoolStack;
  std::condition_variable m_cvPoolStack;

};
}
}
}

#endif //MAGLAC_CORE_MULTITHREAD_TRIGGER_H

