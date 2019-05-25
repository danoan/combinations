#ifndef COMBINATIONS_EXECUTION_H
#define COMBINATIONS_EXECUTION_H

#include "combinations/single-range/eager-recursive.h"
#include "combinations/utils/mockUtils.h"

#include "combinations/logger/logger.h"

namespace Combinations
{
    namespace Test
    {
        bool execution(unsigned int listSize, unsigned int combSize, Logger& logger);
    }
}


#endif //COMBINATIONS_EXECUTION_H
