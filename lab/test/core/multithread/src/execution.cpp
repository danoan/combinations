#include "magLac/lab/test/core/multithread/execution.h"

namespace magLac {
namespace Test {
namespace Multithread {
bool executionMultithread(Logger &logger, size_t numThreads, size_t n, size_t k) {
  logger << Logger::HeaderTwo << "TestExecution" << Logger::Normal;
  logger << "Num Threads:  " << numThreads << "\n"
         << "Num. Elems:  " << n << "\n"
         << "Elems. per comb.: " << k << "\n";

  bool flag = true;
  logger.startTimer();
  try {
    IntVector v = Utils::createIntegerVector(n);
    size_t totalComb = 1;

    for (size_t i = 0; i < k; ++i) totalComb *= (n - i);
    for (size_t i = 1; i <= k; ++i) totalComb /= i;
    size_t queriesPerThread = (size_t) std::ceil(totalComb / (1.0 * numThreads));

    auto range = magLac::Core::addRange(v.begin(), v.end(), k);
    auto combinator = magLac::Core::Combinator(*range);

    ExecutionData data;
    auto planner = slice(combinator, data, numThreads, queriesPerThread);
    typedef decltype(planner)::MyThreadInfo MyThreadInfo;

    logger.startTimer();

    IntVector c1(k);
    planner.run([&c1](MyThreadInfo &&ti) mutable {
      ti.resolver >> c1;
      ti.data.mutableData.cv.push_back(c1);
    });

    logger << "Execution time: ";
    logger.endTimer();

    size_t visitedElems = 0;
    for (auto data:planner) {
      visitedElems += data.mutableData.cv.size();
    }

    logger << "Expected Combinations: " << totalComb << "\n";
    logger << "Computed Combinations: " << visitedElems << "\n\n";

    delete range;
  }
  catch (std::exception &ex) {
    logger << "Error: " << ex.what();
    flag = false;
  }
  logger.endTimer();

  logger << "Passed: " << flag;

  return flag;
}

bool execution(Logger &logger) {
  bool flag = true;
  flag = flag && executionMultithread(logger, 2, 20, 4);
  flag = flag && executionMultithread(logger, 4, 20, 4);
  flag = flag && executionMultithread(logger, 8, 20, 4);
  flag = flag && executionMultithread(logger, 16, 20, 4);

  flag = flag && executionMultithread(logger, 2, 50, 5);
  flag = flag && executionMultithread(logger, 4, 50, 5);
  flag = flag && executionMultithread(logger, 8, 50, 5);
  flag = flag && executionMultithread(logger, 16, 50, 5);

  return flag;
}
}
}
}