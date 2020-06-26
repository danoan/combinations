#ifndef MAGLAC_LAB_BENCHMARK_TECHNIQUES_LAZYRECURSIVE_H
#define MAGLAC_LAB_BENCHMARK_TECHNIQUES_LAZYRECURSIVE_H

#include <vector>
#include <set>

namespace magLac {
namespace LazyRecursive {
template<class TElementType, class TElementIterator>
class LazyCombinator {
 public:
  typedef std::vector<TElementType> CombinationSequence;
  typedef unsigned long int Size;

 private:
  enum Status { FAILURE, CONTINUE, SUCCESS };

 public:
  LazyCombinator(Size combSize,
                 TElementIterator begin,
                 TElementIterator end);

  bool next(CombinationSequence &curr);

 private:
  Status rec_combinations(CombinationSequence &curr,
                          Size k,
                          TElementIterator begin,
                          TElementIterator end);

 private:
  Size combSize;
  TElementIterator begin, end;
  Size lastCombNum;
  Size currCombNum;
};

template<class TElementIterator, class TElementType=typename TElementIterator::value_type>
LazyCombinator<TElementType, TElementIterator> combinations(unsigned long int combSize,
                                                            TElementIterator begin,
                                                            TElementIterator end) {
  return LazyCombinator<TElementType, TElementIterator>(combSize, begin, end);
}
}

}

#include "lazy-recursive.hpp"

#endif //MAGLAC_LAB_BENCHMARK_TECHNIQUES_LAZYRECURSIVE_H
