#ifndef MAGLAC_CORE_BASE_COMBINATOR_H
#define MAGLAC_CORE_BASE_COMBINATOR_H

#include <vector>

#include "magLac/core/base/Range.hpp"
#include "magLac/core/base/Event.h"
#include "magLac/core/base/FundamentalCombinator.h"

#include "Resolver.h"

namespace magLac {
namespace Core {
template<class TRange>
class Combinator {
 public:
  typedef TRange MyRange;
  typedef Resolver<MyRange, TRange::isFirst> MyResolver;
  typedef std::vector<FundamentalCombinator> FundamentalVector;

 private:
  typedef std::stack<Event> EventStack;

 public:
  Combinator(MyRange &range);

  bool next(MyResolver &resolver);

  MyResolver resolver();

 private:
  template<class TResolver>
  void setResolver(TResolver &resolver);

  template<class TResolver>
  void setResolver(TResolver &resolver, size_t proxyVectorIndex);

 private:
  MyRange& m_range;
  FundamentalVector m_fv;

  size_t m_numRanges;
  EventStack m_es;
};

template<class TRange>
void initializeFundamentalVector(std::vector<FundamentalCombinator> &fv, const TRange &range) {
  fv.push_back(FundamentalCombinator(range.length, range.elemsPerComb));
  if (TRange::isFirst) return;
  else initializeFundamentalVector(fv, range.previous);
}

#include "Combinator.hpp"
}
}

#endif//MAGLAC_CORE_BASE_COMBINATOR_H
