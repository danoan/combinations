#ifndef COMBINATIONS_CORRECTENESS_H
#define COMBINATIONS_CORRECTENESS_H

#include <set>

#include "combinations/eager-recursive.h"
#include "combinations/utils/mockUtils.h"

#include "combinations/logger/logger.h"

namespace Combinations
{
    namespace Test
    {
        bool belongsTo(const std::set<int>& currComb,const EagerRecursive::CombinationsVector<int>& combs);

        bool enumeration(unsigned int listSize, unsigned int combSize, EagerRecursive::CombinationsVector<int> checkV, Logger& logger);
        bool numElements(unsigned int listSize, unsigned int combSize, unsigned int checkV, Logger& logger);
        bool correcteness(Logger& logger);
    }
}

#endif //COMBINATIONS_CORRECTENESS_H
