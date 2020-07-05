#ifndef MAGLAC_CORE_MULTITHREAD_THREADINFO_H
#define MAGLAC_CORE_MULTITHREAD_THREADINFO_H

#include "DataChunk.h"
#include "ThreadControl.h"

namespace magLac {
namespace Core {
namespace MultiThread {
template<class TDataChunk>
struct ThreadInfo {
  typedef TDataChunk DataChunk;
  typedef typename DataChunk::MyResolver MyResolver;

  ThreadInfo(MyResolver &resolver, DataChunk &data, ThreadControl &control)
      : resolver(resolver),
        data(data),
        control(control) {}

  MyResolver &resolver;
  DataChunk &data;
  ThreadControl &control;
};
}
}
}

#endif //MAGLAC_CORE_MULTITHREAD_THREADINFO_H
