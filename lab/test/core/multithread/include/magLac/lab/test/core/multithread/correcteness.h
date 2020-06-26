#ifndef MAGLAC_LAB_TEST_CORE_MULTITHREAD_CORRECTENESS_H
#define MAGLAC_LAB_TEST_CORE_MULTITHREAD_CORRECTENESS_H

#include <vector>
#include <set>

#include "magLac/magLac.h"
#include "magLac/multithread.h"

#include "magLac/lab/logger/logger.h"
#include "magLac/lab/utils/mockUtils.h"
#include "magLac/lab/utils/displayUtils.h"

namespace magLac {
namespace Test {
namespace Multithread {
typedef std::vector<int> IntVector;

typedef std::vector<IntVector> CombinationsContainer;
typedef std::vector<std::set<int> > CombinationsCheckContainer;

struct CorrectData {
  struct MutableData {
    void restart() {};
    std::vector<IntVector> cv;
  };

  struct ConstantData {

  };

  MutableData mutableData;
  ConstantData constantData;
};

bool belongsTo(const std::set<int> &currComb, const CombinationsContainer &combs);
bool correctenessMultithread(Logger &logger, size_t numThreads, size_t n, size_t k, const CombinationsCheckContainer &checkV);
bool correcteness(Logger &logger);
}
}
}

#endif //MAGLAC_LAB_TEST_CORE_MULTITHREAD_CORRECTENESS_H
