#ifndef COMBINATIONS_EXECUTION_H
#define COMBINATIONS_EXECUTION_H

#include "magLac/lab/logger/logger.h"
#include "magLac/core/base/FundamentalCombinator.h"

namespace magLac
{
    namespace Test
    {
        typedef unsigned long int Size;

        bool fundamentalCombinator(Size numElems, Size elemsPerComb,Logger& logger);
        bool execution(Logger& logger);
    }
}

#endif //COMBINATIONS_EXECUTION_H
