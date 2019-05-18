#ifndef SINGLE_RANGE_COMBINATOR_H
#define SINGLE_RANGE_COMBINATOR_H

#include <vector>
#include <stack>

#include "Event.h"

template<class TType>
class SingleRangeCombinator
{
public:
  typedef TType MyType;
  typedef SingleRangeCombinator<MyType> Self;

  typedef std::vector<MyType> MyVector;
  typedef typename MyVector::const_iterator MyVectorIterator;

  typedef unsigned long int Size;

private:
  typedef std::stack<Event> EventStack;

private:
  inline MyVectorIterator moveIt(MyVectorIterator it, Size steps) const
  { for(;steps>0;--steps) ++it; return it; }

public:
  SingleRangeCombinator(Size elemsPerComb,
    MyVectorIterator begin,
    MyVectorIterator end);

  bool next(MyVector& nextComb);
  void restart();

private:
  EventStack es;
  MyVector currComb;

  const MyVectorIterator begin,end;

public:
    const Size elemsPerComb;
};

#include "SingleRangeCombinator.hpp"

#endif
