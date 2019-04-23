#include <iostream>
#include <vector>

#include "base/Range.hpp"

#include "multiple/Resolver.h"
#include "single/Resolver.h"
#include "utils.h"

void fromRange()
{
  typedef unsigned long int Size;

  IntVector v = {1,2,3,4,5,6,7,8,9,10};

  auto b1 = v.begin();
  auto e1 = v.begin()+3;

  auto b2 = v.begin()+3;
  auto e2 = v.begin()+6;

  auto b3 = v.begin()+6;
  auto e3 = v.end();

  auto range = addRange(b1,e1,2).addRange(b2,e2,2).addRange(b3,e3,2);
  auto mr = Multiple::createResolver(range);

  std::vector<Size> hops1 = {0,1};
  std::vector<Size> hops2 = {0,2};
  std::vector<Size> hops3 = {1,2};

  mr.set(hops1);
  auto& previous = mr.previousSolver;
  previous.set(hops2);
  auto& previous2 = previous.previousSolver;
  previous2.set(hops3);

  std::vector<int> c1(2);
  std::vector<int> c2(2);
  std::vector<int> c3(2);

  mr >> c1 >> c2 >> c3;

  CombinationsVector cv;
  cv.push_back(c1);cv.push_back(c2);cv.push_back(c3);

  printCombinations(cv.begin(),cv.end());

  std::cout << "OK!" << std::endl;
}

int main()
{

  fromRange();

  return 0;
}
