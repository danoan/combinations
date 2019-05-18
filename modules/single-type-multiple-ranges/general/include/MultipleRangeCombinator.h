#ifndef MULTIPLE_RANGE_COMBINATOR_H
#define MULTIPLE_RANGE_COMBINATOR_H

#include <vector>
#include "SingleRangeCombinator.h"
#include "IndexableSingleRangeCombinator.h"
#include "CurrentCombination.h"

template<class TType>
class MultipleRangeCombinator
{
public:
    typedef TType MyType;
    typedef MultipleRangeCombinator<MyType> Self;

    typedef IndexableSingleRangeCombinator<MyType> MyIndexableSingleRangeCombinator;
    typedef typename MyIndexableSingleRangeCombinator::MySingleRangeCombinator MySingleRangeCombinator;
    
    typedef std::vector<MyIndexableSingleRangeCombinator> MySingleRangeCombinatorVector;
    typedef typename MySingleRangeCombinatorVector::iterator MySingleRangeCombinatorVectorIterator;

    typedef std::vector<MyType> MyVector;
    typedef typename MyVector::const_iterator MyVectorIterator;

    typedef CurrentCombination<MyType> MyCurrentCombination;

    typedef unsigned long int Size;



  private:
    typedef std::stack<Event> EventStack;

public:
  MultipleRangeCombinator();
  void addRange(Size combSize, MyVectorIterator begin, MyVectorIterator end);
  void addRange(MyVectorIterator begin, MyVectorIterator end);

  bool next(MyVector& combVector);

private:
  inline MySingleRangeCombinatorVectorIterator moveIt(
    MySingleRangeCombinatorVectorIterator it,
    Size steps) const
  { for(;steps>0;--steps) ++it; return it; }

private:
  bool flagInitState;

  Size numRanges;
  EventStack es;

  MyCurrentCombination currComb;
  MySingleRangeCombinatorVector srcv;
};

#include "MultipleRangeCombinator.hpp"

#endif
