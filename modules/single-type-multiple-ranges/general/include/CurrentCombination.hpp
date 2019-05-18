#include "CurrentCombination.h"

template<class TType>
void CurrentCombination<TType>::init(const MyIndexableCombinatorVector& icv)
{
  Size index=0;
  for(auto it=icv.begin();it!=icv.end();++it)
  {
    icm[*it] = index;
    index+= it->combinator.elemsPerComb;
  }

  currComb.resize(index);
}

template<class TType>
void CurrentCombination<TType>::update(const MyIndexableSingleRangeCombinator& ic,
  const MyVector& combVector)
{
  Size index = icm[ic];
  for(auto it=combVector.begin();it!=combVector.end();++it)
  {
    currComb[index++] = *it;
  }
}
