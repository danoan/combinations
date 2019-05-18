#ifndef SINGLE_RANGE_COMBINATOR_H
#define SINGLE_RANGE_COMBINATOR_H

#include <vector>
#include <stack>

#include "Event.h"

class SingleRangeCombinator
{
public:
  typedef unsigned long int Size;

public:
  typedef std::vector<int> IntVector;
  typedef IntVector::const_iterator IntIterator;

private:
  typedef std::stack<Event> EventStack;

private:
  inline IntIterator moveIt(IntIterator it, Size steps) const{ for(;steps>0;--steps) ++it; return it; }

public:
  SingleRangeCombinator(Size elemsPerComb, IntIterator begin, IntIterator end);
  bool next(IntVector& nextComb);
  void restart();

private:
  EventStack es;
  IntVector currComb;

  const IntIterator begin,end;

public:
    const Size elemsPerComb;
};

#endif
