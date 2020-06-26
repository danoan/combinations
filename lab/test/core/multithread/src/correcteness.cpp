#include "magLac/lab/test/core/multithread/correcteness.h"

namespace magLac {
namespace Test {
namespace Multithread {
bool belongsTo(const std::set<int> &currComb, const CombinationsContainer &combs) {
  for (auto itU = combs.cbegin(); itU != combs.cend(); ++itU) {
    bool found = true;
    for (auto it = itU->cbegin(); it != itU->cend(); ++it) {
      if (currComb.find(*it) == currComb.end()) {
        found = false;
        break;
      }
    }

    if (found) return true;
  }

  return false;
}

bool correctenessMultithread(Logger &logger,
                             size_t numThreads,
                             size_t n,
                             size_t k,
                             const CombinationsCheckContainer &checkV) {
  logger << Logger::HeaderTwo << "TestCorrecteness" << Logger::Normal;
  logger << "Num Threads: " << numThreads << "\n"
         << "Num. Elems: " << n << "\n"
         << "Elems. per comb.: " << k << "\n";

  IntVector v = Utils::createIntegerVector(n);
  size_t totalComb = 1;

  for (size_t i = 0; i < k; ++i) totalComb *= (n - i);
  for (size_t i = 1; i <= k; ++i) totalComb /= i;
  size_t queriesPerThread = (size_t) std::ceil(totalComb / (1.0 * numThreads));

  auto range = magLac::Core::addRange(v.begin(), v.end(), k);
  auto combinator = magLac::Core::Combinator(range);

  CorrectData data;
  auto planner = slice(combinator, data, numThreads, queriesPerThread);
  typedef decltype(planner)::MyThreadInfo MyThreadInfo;

  IntVector c1(k);
  planner.run([&c1](MyThreadInfo &&ti) mutable {
    ti.resolver >> c1;
    ti.data.mutableData.cv.push_back(c1);
    c1.clear();
  });

  CombinationsContainer combinations;
  size_t visitedElems = 0;
  for (auto data:planner) {
    const CombinationsContainer &cc = data.mutableData.cv;
    visitedElems += cc.size();

    combinations.insert(combinations.end(), cc.begin(), cc.end());
  }

  logger << "Expected Combinations: " << totalComb << "\n";
  logger << "Computed Combinations: " << visitedElems << "\n\n";

  for (auto it = checkV.begin(); it != checkV.end(); ++it) {
    if (!belongsTo(*it, combinations)) {
      logger << "Passed: false\n";

      logger << "Computed: \n";
      Utils::printCombinations(combinations.begin(), combinations.end(), logger.stream());

      logger << "Expected: \n";
      Utils::printCombinations(checkV.begin(), checkV.end(), logger.stream());

      return false;
    }
  }

  logger << "Passed: true\n";

  return totalComb == visitedElems;
}

bool correcteness(Logger &logger) {
  bool flag = true;
  const CombinationsCheckContainer checkV = {{1, 2, 3}, {1, 2, 4}, {1, 2, 5}, {1, 2, 6},
                                             {1, 3, 4}, {1, 3, 5}, {1, 3, 6},
                                             {1, 4, 5}, {1, 4, 6},
                                             {1, 5, 6},
                                             {2, 3, 4}, {2, 3, 5}, {2, 3, 6},
                                             {2, 4, 5}, {2, 4, 6},
                                             {2, 5, 6},
                                             {3, 4, 5}, {3, 4, 6},
                                             {3, 5, 6},
                                             {4, 5, 6}};

  flag = flag && correctenessMultithread(logger, 1, 6, 3, checkV);
  flag = flag && correctenessMultithread(logger, 2, 6, 3, checkV);
  flag = flag && correctenessMultithread(logger, 3, 6, 3, checkV);
  flag = flag && correctenessMultithread(logger, 4, 6, 3, checkV);

  return flag;
}
}
}
}