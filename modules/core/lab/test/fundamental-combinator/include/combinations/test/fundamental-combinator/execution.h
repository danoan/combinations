#ifndef COMBINATIONS_EXECUTION_H
#define COMBINATIONS_EXECUTION_H

#include "combinations/logger/logger.h"
#include "combinations/core/base/FundamentalCombinator.h"

namespace Combinations
{
    namespace Test
    {
        typedef unsigned long int Size;

        bool fundamentalCombinator(Size numElems, Size elemsPerComb,Logger& logger);
        bool execution(Logger& logger);
    }
}

#endif //COMBINATIONS_EXECUTION_H
