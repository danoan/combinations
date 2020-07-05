#ifndef MAGLAC_LAB_TEST_CORE_FUNDAMENTALCOMBINATOR_CORRECTENESS_H
#define MAGLAC_LAB_TEST_CORE_FUNDAMENTALCOMBINATOR_CORRECTENESS_H

#include <vector>
#include <set>

#include "magLac/core/base/FundamentalCombinator.h"
#include "magLac/lab/logger/logger.h"
#include "magLac/lab/utils/displayUtils.h"

namespace magLac {
namespace Test {
namespace FundamentalCombinator {
typedef std::vector<std::vector<size_t> > CombinationsContainer;
typedef std::vector<std::set<size_t> > CombinationsCheckContainer;

bool belongsTo(const std::set<size_t> &currComb, const CombinationsContainer &combs);
bool fundamentalCombinator(size_t numElems, size_t elemsPerComb, const CombinationsCheckContainer &checkV, Logger &logger);
bool correcteness(Logger &logger);
}
}
}

#endif //MAGLAC_LAB_TEST_CORE_FUNDAMENTALCOMBINATOR_CORRECTENESS_H
