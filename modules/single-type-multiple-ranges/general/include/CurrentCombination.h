#ifndef CURRENT_COMBINATION_H
#define CURRENT_COMBINATION_H

#include <vector>
#include <map>

#include "IndexableSingleRangeCombinator.h"

template<class TType>
class CurrentCombination
{
public:
  typedef TType MyType;

  typedef IndexableSingleRangeCombinator<MyType> MyIndexableSingleRangeCombinator;
  typedef std::vector<MyIndexableSingleRangeCombinator> MyIndexableCombinatorVector;
  typedef std::vector<MyType> MyVector;
  typedef typename MyVector::const_iterator IntIterator;

private:
  typedef unsigned long int Size;
  typedef std::map<MyIndexableSingleRangeCombinator,Size> IndexableCombinatorMap;


public:
  CurrentCombination(){};

  void init(const MyIndexableCombinatorVector& icv);
  void update(const MyIndexableSingleRangeCombinator& ic,
    const MyVector& combVetor);

  const MyVector& operator()(){return currComb;}

private:
  IndexableCombinatorMap icm;
  MyVector currComb;
};

#include "CurrentCombination.hpp"

#endif
