#include "utils.h"

IntVector createIntegerVector(int nelems)
{
  std::vector<int> intVector;
  int x=1;
  while(nelems>0)
  {
    intVector.push_back(x++);
    --nelems;
  }

  return intVector;
}

void printCombinations(CombinationsIterator begin,
  CombinationsIterator end)
{
  for(auto itc=begin;itc!=end;++itc)
  {
    for(auto iti=itc->begin();iti!=itc->end();++iti)
    {
      std::cout << *iti << ",";
    }
    std::cout << "\n";
  }
}
