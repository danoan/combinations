#include <iostream>
#include <vector>

#include "combinations/core/base/Range.hpp"
#include "combinations/core/single/Combinator.hpp"
#include "combinations/utils/displayUtils.h"

using namespace Combinations;
using namespace Combinations::MultipleRanges;

int main()
{
  std::vector<int> v = {1,2,3,4,5};
  unsigned long int elemsPerComb = 3;

  auto range = addRange(v.begin(),v.end(),elemsPerComb);
  auto combinator = Single::createCombinator(range);
  auto resolver = combinator.resolver();

  std::vector<int> nextComb(elemsPerComb);
  std::vector< std::vector<int> > cv;
  while(combinator.next(resolver))
  {
    resolver >> nextComb;
    cv.push_back(nextComb);
  }

  Utils::printCombinations<int>(cv.begin(),cv.end());

  return 0;
}
