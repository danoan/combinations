#ifndef INDEXABLE_SINGLE_RANGE_COMBINATOR_H
#define INDEXABLE_SINGLE_RANGE_COMBINATOR_H

#include "SingleRangeCombinator.h"

template<class TType>
class IndexableSingleRangeCombinator
{
public:
  typedef TType MyType;
  typedef IndexableSingleRangeCombinator<MyType> Self;
  typedef SingleRangeCombinator<MyType> MySingleRangeCombinator;

  typedef unsigned long int Size;

  IndexableSingleRangeCombinator(Size index,
    const MySingleRangeCombinator& combinator):
  index(index),combinator(combinator){}

  bool operator< (const Self& other)const
  { return this->index < other.index; }

  Size index;
  MySingleRangeCombinator combinator;
};

namespace std
{
  template<class TType>
  struct hash<IndexableSingleRangeCombinator<TType>>
  {
    size_t operator()(const IndexableSingleRangeCombinator<TType>& el)
    {
      return std::hash<size_t>().operator()(el.index);
    }
  };
}

#endif
