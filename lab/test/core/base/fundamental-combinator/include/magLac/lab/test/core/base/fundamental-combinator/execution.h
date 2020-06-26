#ifndef MAGLAC_LAB_TEST_CORE_FUNDAMENTALCOMBINATOR_EXECUTION_H
#define MAGLAC_LAB_TEST_CORE_FUNDAMENTALCOMBINATOR_EXECUTION_H

#include "magLac/lab/logger/logger.h"
#include "magLac/core/base/FundamentalCombinator.h"

namespace magLac {
namespace Test {
namespace FundamentalCombinator {

bool fundamentalCombinator(size_t numElems, size_t elemsPerComb, Logger &logger);
bool execution(Logger &logger);
}
}
}

#endif //MAGLAC_LAB_TEST_CORE_FUNDAMENTALCOMBINATOR_EXECUTION_H
