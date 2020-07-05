#include "magLac/magLac.h"
#include "magLac/multithread.h"

#include "magLac/lab/utils/displayUtils.h"
#include "magLac/lab/utils/mockUtils.h"
#include "magLac/lab/logger/logger.h"

using namespace magLac;

typedef std::vector<int> IntVector;

struct MyThreadData {
  struct MutableData {
    void restart() {};
    std::vector<IntVector> cv;
  };

  struct ConstantData {

  };

  MutableData mutableData;
  ConstantData constantData;
};

int main(int argc, char *argv[]) {
  unsigned int numThreads = 4;
  unsigned int queriesPerThread = 10;

  auto combExplorer = takeFromEach<2>({1, 2, 3}, {4, 5, 6}, {7, 8, 9, 10});

  MyThreadData data;
  auto theThread = slice(combExplorer.combinator(), data, numThreads, queriesPerThread);
  typedef decltype(theThread)::MyThreadInfo MyThreadInfo;

  theThread.run([](MyThreadInfo &&ti) mutable {
    IntVector c1(2), c2(2), c3(2), unionV;
    ti.resolver >> c1 >> c2 >> c3;

    unionV.insert(unionV.end(), c1.begin(), c1.end());
    unionV.insert(unionV.end(), c2.begin(), c2.end());
    unionV.insert(unionV.end(), c3.begin(), c3.end());

    ti.data.mutableData.cv.push_back(unionV);
  });

  int totalCombs = 0;
  for (auto data:theThread) {
    const std::vector<IntVector> &cv = data.mutableData.cv;
    totalCombs += cv.size();
    Utils::printCombinations(cv.begin(), cv.end());
  }

  std::cout << "\n" << totalCombs << " combinations!\n\n";

  return 0;
}