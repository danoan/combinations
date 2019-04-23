#ifndef MULTIPLE_RANGE_COMBINATOR_H
#define MULTIPLE_RANGE_COMBINATOR_H

#include <vector>
#include "SingleRangeCombinator.h"
#include "IndexableSingleRangeCombinator.h"
#include "CurrentCombination.h"

class MultipleRangeCombinator
{
public:
    typedef unsigned long int Size;

    typedef std::vector<IndexableSingleRangeCombinator> SingleRangeCombinatorVector;
    typedef SingleRangeCombinatorVector::iterator SingleRangeCombinatorVectorIterator;

    typedef std::vector<int> IntVector;
    typedef IntVector::const_iterator IntIterator;

  private:
    typedef std::stack<Event> EventStack;

public:
  MultipleRangeCombinator();
  void addRange(Size combSize, IntIterator begin, IntIterator end);
  void addRange(IntIterator begin, IntIterator end);

  bool next(IntVector& combVector);

private:
  inline SingleRangeCombinatorVectorIterator moveIt(
    SingleRangeCombinatorVectorIterator it,
    Size steps) const
  { for(;steps>0;--steps) ++it; return it; }

private:
  bool flagInitState;

  Size numRanges;
  EventStack es;

  CurrentCombination currComb;
  SingleRangeCombinatorVector srcv;
};

#endif
