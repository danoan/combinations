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
typedef unsigned long int Size;
typedef std::vector<std::vector<Size> > CombinationsContainer;
typedef std::vector<std::set<Size> > CombinationsCheckContainer;

bool belongsTo(const std::set<Size> &currComb, const CombinationsContainer &combs);
bool fundamentalCombinator(Size numElems, Size elemsPerComb, const CombinationsCheckContainer &checkV, Logger &logger);
bool correcteness(Logger &logger);
}
}
}

#endif //MAGLAC_LAB_TEST_CORE_FUNDAMENTALCOMBINATOR_CORRECTENESS_H
