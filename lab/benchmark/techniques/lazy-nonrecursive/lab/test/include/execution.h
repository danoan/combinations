#ifndef MAGLAC_LAB_BENCHMARK_TECHNIQUES_LAZYNONRECURSIVE_EXECUTION_H
#define MAGLAC_LAB_BENCHMARK_TECHNIQUES_LAZYNONRECURSIVE_EXECUTION_H

#include "lazy-nonrecursive.h"

#include "magLac/lab/utils/mockUtils.h"
#include "magLac/lab/logger/logger.h"

namespace magLac {
namespace Test {
bool execution(unsigned int listSize, unsigned int combSize, Logger &logger);
}
}

#endif //MAGLAC_LAB_BENCHMARK_TECHNIQUES_LAZYNONRECURSIVE_EXECUTION_H
