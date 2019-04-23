#ifndef SINGLE_RANGE_COMBINATOR_H
#define SINGLE_RANGE_COMBINATOR_H

#include <vector>
#include <stack>

#include "Event.h"
#include "Range.hpp"
#include "SingleResolver.h"

template<class TRange>
class SingleRangeCombinator
{
public:
  typedef TRange MyRange;
  typedef typename MyRange::IteratorType MyIterator;
  typedef SingleResolver<MyIterator> MyResolver;

  typedef unsigned long int Size;
  typedef std::vector<Size> VectorOfHops;

private:
  typedef std::stack<Event> EventStack;

public:
  SingleRangeCombinator(MyRange range);

  bool next(MyResolver& resolver);
  void restart();

  MyResolver resolver();

public:
  EventStack es;
  MyRange range;
  VectorOfHops currHops;

public:
    const Size elemsPerComb;
};

template<typename TRange>
SingleRangeCombinator<TRange> createSingleRangeCombinator(TRange range)
  {
    return SingleRangeCombinator<TRange>(range);
  }

#include "SingleRangeCombinator.hpp"

#endif
