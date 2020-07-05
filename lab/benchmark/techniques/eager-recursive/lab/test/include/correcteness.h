#ifndef MAGLAC_LAB_BENCHMARK_TECHNIQUES_EAGERRECURSIVE_LAB_TEST_CORRECTENESS_H
#define MAGLAC_LAB_BENCHMARK_TECHNIQUES_EAGERRECURSIVE_LAB_TEST_CORRECTENESS_H

#include <set>

#include "eager-recursive.h"

#include "magLac/lab/utils/mockUtils.h"
#include "magLac/lab/logger/logger.h"

namespace magLac {
namespace Test {
bool belongsTo(const std::set<int> &currComb, const EagerRecursive::CombinationsVector<int> &combs);

bool enumeration(unsigned int listSize,
                 unsigned int combSize,
                 EagerRecursive::CombinationsVector<int> checkV,
                 Logger &logger);
bool numElements(unsigned int listSize, unsigned int combSize, unsigned int checkV, Logger &logger);
bool correcteness(Logger &logger);
}
}

#endif //MAGLAC_LAB_BENCHMARK_TECHNIQUES_EAGERRECURSIVE_LAB_TEST_CORRECTENESS_H
