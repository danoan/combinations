#include <iostream>
#include <random>

#include "MultipleRangeCombinator.h"
#include "utils.h"

struct InputRange
{
  InputRange(int listSize, int combSize):listSize(listSize),combSize(combSize){}

  int listSize;
  int combSize;
};

void multipleList(const std::vector<InputRange>& inputRangeVector)
{
  MultipleRangeCombinator<int> mrc;

  std::vector< IntVector > container;
  for(auto it=inputRangeVector.begin();it!=inputRangeVector.end();++it)
  {
    container.push_back( createIntegerVector(it->listSize) );
    const IntVector& last = container[container.size()-1];
    mrc.addRange(it->combSize,last.begin(),last.end());
  }

  CombinationsVector cv;
  IntVector combVector;
  while(mrc.next(combVector))
  {
    cv.push_back(combVector);
  }

  std::cout << "\n Combinations count: " << cv.size() << "\n\n";
  printCombinations(cv.begin(),cv.end());
}



int main(int argc, char* argv[])
{
  /*
    Example:
      ./multiple-ranges 3 5 1 5 1 5 1

      Should return 125 elements;
  */
  if(argc<2)
  {
    std::cout << "\nUSAGE: lazy-nonrecursive numElements (listSize_1, combSize_1) ... \n";
    exit(1);
  }

  std::vector<InputRange> inputRangeVector;
  int numElements = std::atoi(argv[1]);
  int maxArgIndex = 2 + numElements*2;
  for(int argIndex=2;argIndex<maxArgIndex;)
  {
    int listSize = std::atoi(argv[argIndex++]);
    int combSize = std::atoi(argv[argIndex++]);
    inputRangeVector.push_back( InputRange( listSize,combSize ) );
  }

  multipleList(inputRangeVector);


  return 0;
}
