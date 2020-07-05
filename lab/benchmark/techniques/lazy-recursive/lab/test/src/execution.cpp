#include "execution.h"

namespace magLac {
namespace Test {
bool execution(unsigned int listSize, unsigned int combSize, Logger &logger) {
  logger.startTimer();
  bool flag = false;
  try {
    logger << Logger::HeaderTwo << "Test Execution" << Logger::Normal;
    logger << "List Size: " << listSize << "\n";
    logger << "Comb Size: " << combSize << "\n";

    auto intVector = Utils::createIntegerVector(listSize);
    auto combGenerator = LazyRecursive::combinations(combSize,
                                                     intVector.begin(),
                                                     intVector.end());

    typedef decltype(combGenerator) MyLazyCombinator;
    typedef MyLazyCombinator::CombinationSequence CombinationSequence;

    unsigned long int size = 0;
    CombinationSequence cs;
    while (combGenerator.next(cs)) ++size;

    logger << "Combinations Counts: " << size << "\n";
    flag = true;
  } catch (std::exception &ex) {
    logger << "Error: " << ex.what() << "\n";
    flag = false;
  }

  logger << "Execution time: ";
  logger.endTimer();
  return flag;
}
}
}