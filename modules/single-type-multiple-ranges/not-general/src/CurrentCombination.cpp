#include "CurrentCombination.h"

void CurrentCombination::init(const IndexableCombinatorVector& icv)
{
  Size index=0;
  for(auto it=icv.begin();it!=icv.end();++it)
  {
    icm[*it] = index;
    index+= it->combinator.elemsPerComb;
  }

  currComb.resize(index);
}

void CurrentCombination::update(const IndexableSingleRangeCombinator& ic,
  const IntVector& combVector)
{
  Size index = icm[ic];
  for(auto it=combVector.begin();it!=combVector.end();++it)
  {
    currComb[index++] = *it;
  }
}
