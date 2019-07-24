#ifndef COMBINATIONS_EXECUTION_H
#define COMBINATIONS_EXECUTION_H

#include "lazy-recursive.h"

#include "magLac/lab/utils/mockUtils.h"
#include "magLac/lab/logger/logger.h"

namespace magLac
{
    namespace Test
    {
        bool execution(unsigned int listSize, unsigned int combSize, Logger& logger);
    }
}


#endif //COMBINATIONS_EXECUTION_H
