#include <iostream>
#include <random>

#include "MultipleRangeCombinator.h"
#include "utils.h"

int main()
{
  MultipleRangeCombinator<int> mrcInt;
  MultipleRangeCombinator<double> mrcDouble;

  std::vector<int> rangeInt = createIntegerVector(3);
  std::vector<double> rangeDouble = {0.2,0.4,0.6};

  mrcInt.addRange(1,rangeInt.begin(),rangeInt.end());
  mrcInt.addRange(1,rangeInt.begin(),rangeInt.end());
  mrcDouble.addRange(1,rangeDouble.begin(),rangeDouble.end());

  std::vector<double> t;
  mrcDouble.next(t);
  std::cout << t[0] << std::endl;

  return 0;
}
