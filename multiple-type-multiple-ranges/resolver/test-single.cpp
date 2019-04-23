#include <iostream>
#include <vector>

#include "SingleRangeCombinator.h"
#include "Range.hpp"
#include "utils.h"

int main()
{
  std::vector<int> v = {1,2,3,4,5};
  unsigned long int elemsPerComb = 3;

  auto range = addRange(v.begin(),v.end(),elemsPerComb);
  auto combinator = createSingleRangeCombinator(range);
  auto resolver = combinator.resolver();

  std::vector<int> nextComb(elemsPerComb);
  CombinationsVector cv;
  while(combinator.next(resolver))
  {
    resolver >> nextComb;
    cv.push_back(nextComb);
  }

  printCombinations(cv.begin(),cv.end());

  return 0;
}
