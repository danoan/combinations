#ifndef MAGLAC_CORE_MULTITHREAD_THREADINPUT_H
#define MAGLAC_CORE_MULTITHREAD_THREADINPUT_H

namespace magLac {
namespace Core {
namespace MultiThread {
template<class TCombinator, class TThreadData>
struct DataChunk {
  typedef TCombinator MyCombinator;
  typedef typename TCombinator::MyResolver MyResolver;

  typedef TThreadData ThreadData;
  typedef typename ThreadData::ConstantData ConstantData;
  typedef typename ThreadData::MutableData MutableData;

  typedef DataChunk<MyCombinator, ThreadData> Self;

  DataChunk() {}

  DataChunk(MyCombinator *combinatorPt,
            const ConstantData &constantData)
      : combinatorPt(combinatorPt),
        constantData(constantData) {}

  void restart() {
    mutableData.restart();
  }

  MyCombinator *combinatorPt;
  const ConstantData &constantData;
  MutableData mutableData;

};
}
}

}

#endif //MAGLAC_CORE_MULTITHREAD_THREADINPUT_H
