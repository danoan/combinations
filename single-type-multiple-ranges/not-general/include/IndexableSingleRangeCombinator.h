#ifndef INDEXABLE_SINGLE_RANGE_COMBINATOR_H
#define INDEXABLE_SINGLE_RANGE_COMBINATOR_H

#include "SingleRangeCombinator.h"

struct IndexableSingleRangeCombinator
{
  typedef unsigned long int Size;

  IndexableSingleRangeCombinator(Size index,
    const SingleRangeCombinator& combinator):
  index(index),combinator(combinator){}

  bool operator< (const IndexableSingleRangeCombinator& other)const
  { return this->index < other.index; }

  Size index;
  SingleRangeCombinator combinator;
};

namespace std
{
  template<>
  struct hash<IndexableSingleRangeCombinator>
  {
    size_t operator()(const IndexableSingleRangeCombinator& el)
    {
      return std::hash<size_t>().operator()(el.index);
    }
  };
}

#endif
