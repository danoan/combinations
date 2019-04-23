#ifndef CURRENT_COMBINATION_H
#define CURRENT_COMBINATION_H

#include <vector>
#include <map>

#include "IndexableSingleRangeCombinator.h"

class CurrentCombination
{
private:
  typedef unsigned long int Size;
  typedef std::map<IndexableSingleRangeCombinator,Size> IndexableCombinatorMap;

public:
  typedef std::vector<IndexableSingleRangeCombinator> IndexableCombinatorVector;
  typedef std::vector<int> IntVector;
  typedef IntVector::const_iterator IntIterator;

public:
  CurrentCombination(){};
  void init(const IndexableCombinatorVector& icv);

  void update(const IndexableSingleRangeCombinator& ic,
    const IntVector& combVetor);

  const IntVector& operator()(){return currComb;}

private:
  IndexableCombinatorMap icm;
  IntVector currComb;
};

#endif
