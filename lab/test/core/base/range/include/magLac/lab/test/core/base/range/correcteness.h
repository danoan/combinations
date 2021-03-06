#ifndef MAGLAC_LAB_TEST_CORE_RANGE_CORRECTENESS_H
#define MAGLAC_LAB_TEST_CORE_RANGE_CORRECTENESS_H

#include <set>

#include "magLac/core/base/Range.hpp"
#include "magLac/lab/logger/logger.h"

namespace magLac {
namespace Test {
namespace Range {
template<class TIterator, class TValueType=typename TIterator::value_type>
bool check(TIterator begin, TIterator end, const std::set<TValueType> &checkSet) {
  for (auto it = begin; it != end; ++it) {
    if (checkSet.find(*it) == checkSet.end()) return false;
  }

  return true;
}

bool correcteness(Logger &logger);
}
}
}

#endif //MAGLAC_LAB_TEST_CORE_RANGE_CORRECTENESS_H
