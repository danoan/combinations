#ifndef MULTIPLE_RANGE_COMBINATOR_H
#define MULTIPLE_RANGE_COMBINATOR_H

#include <vector>

#include "SingleRangeCombinator.h"
#include "MultipleResolver.h"
#include "Range.hpp"
#include "Event.h"

struct Proxy
{
  typedef unsigned long int Size;
  typedef std::vector<Size> VectorOfHops;
  typedef VectorOfHops::iterator HopsIterator;

  typedef Range<HopsIterator> RangeHops;
  typedef SingleRangeCombinator<RangeHops> ProxyCombinator;

  typedef SingleResolver<HopsIterator> MyResolver;

private:
  static VectorOfHops createProxyVector(Size length)
  {
    VectorOfHops hops(length);
    for(Size i=0;i<length;++i) hops[i] = i;

    return hops;
  }

  static ProxyCombinator createProxyCombinator(VectorOfHops& hops,Size elemsPerComb)
  {
    RangeHops rangeHops = addRange(hops.begin(),
    hops.end(),elemsPerComb);

    return ProxyCombinator(rangeHops);
  }

public:
  template<typename TRange>
  Proxy(const TRange& range):
  proxyVector(createProxyVector(range.length)),
  combinator(createProxyCombinator(this->proxyVector,range.elemsPerComb))
  {
    currHops.resize(range.elemsPerComb);
  }

  MyResolver resolver()
  {
    return MyResolver();
  }

  VectorOfHops proxyVector;
  VectorOfHops currHops;
  ProxyCombinator combinator;
};

template<class TRange>
class MultipleRangeCombinator
{
public:
    //assert that Range is composed of at least 2 ranges.
    typedef TRange MyRange;
    typedef MultipleResolver<MyRange,false> MyResolver;
    typedef std::vector<Proxy> ProxyVector;

    typedef unsigned long int Size;

  private:
    typedef std::stack<Event> EventStack;

public:
  MultipleRangeCombinator(MyRange& range);
  bool next(MyResolver& resolver);

  MyResolver resolver();

private:
  template<class TResolver>
  void setResolver(TResolver& resolver)
  {
    setResolver(resolver,numRanges-1);
  }

  template<class TResolver>
  void setResolver(TResolver& resolver,Size proxyVectorIndex)
  {
    resolver.set(pv[proxyVectorIndex].currHops);
    if(proxyVectorIndex>0) setResolver(resolver.previousSolver,proxyVectorIndex-1);
  }

private:
  MyRange& range;
  ProxyVector pv;

  Size numRanges;
  EventStack es;
};

template<class TRange>
void initializeProxyVector(std::vector<Proxy>& proxyVector, const TRange& range)
{
  proxyVector.push_back(Proxy(range));
  if(TRange::isFirst) return;
  else initializeProxyVector(proxyVector,range.previous);
}

template<class TRange>
void initializeProxyVectorEnd(std::vector<Proxy>& proxyVector, const TRange& range)
{
  proxyVector.push_back(Proxy(range));
}

template<class TRange>
MultipleRangeCombinator<TRange> createMultipleRangeCombinator(TRange& range)
{
  return MultipleRangeCombinator<TRange>(range);
}

#include "MultipleRangeCombinator.hpp"

#endif
