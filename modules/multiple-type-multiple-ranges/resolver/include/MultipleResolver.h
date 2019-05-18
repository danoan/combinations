#ifndef MULTIPLE_RESOLVER_H
#define MULTIPLE_RESOLVER_H

#include "SingleResolver.h"

template< class TRange,bool=TRange::isFirst>
class MultipleResolver{};

template<class TRange>
class MultipleResolver<TRange,true>
{
public:
  typedef unsigned long int Size;
  typedef std::vector<Size> VectorOfHops;

  typedef MultipleResolver<TRange,true> Self;

public:
  MultipleResolver(TRange& range):range(range),previousSolver(*this){};

  void set(const VectorOfHops& hops){this->hops=hops;}

  template<typename TContainer>
  void solve(TContainer& container)
  {
    auto sr = createSingleResolver(range.begin);
    sr(range.begin,range.end,hops);
    sr >> container;
  }

public:
  TRange range;
  VectorOfHops hops;

  Self& previousSolver;
};


template<class TRange>
class MultipleResolver<TRange,false>
{
public:
  typedef unsigned long int Size;
  typedef std::vector<Size> VectorOfHops;

  typedef typename TRange::PreviousRange PreviousRange;
  typedef MultipleResolver<PreviousRange,PreviousRange::isFirst> PreviousSolver;

public:
  MultipleResolver(TRange& range):range(range),
  previousSolver(PreviousSolver(range.previous)){}

  void set(const VectorOfHops& hops){this->hops=hops;}

  template<typename TContainer>
  PreviousSolver& solve(TContainer& container)
  {
    auto sr = createSingleResolver(range.begin);
    sr(range.begin,range.end,hops);
    sr >> container;

    return previousSolver;
  }

public:
  TRange range;
  VectorOfHops hops;

  PreviousSolver previousSolver;
};

template<class TRange>
MultipleResolver<TRange> createMultipleResolver(TRange& range)
{
  return MultipleResolver<TRange>(range);
}

#endif
