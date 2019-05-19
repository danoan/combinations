#ifndef COMBINATIONS_CORRECTENESS_H
#define COMBINATIONS_CORRECTENESS_H

#include <set>

#include "combinations/lazy-recursive.h"
#include "combinations/utils/mockUtils.h"

#include "combinations/logger/logger.h"

namespace Combinations
{
    namespace Test
    {
        typedef std::set< std::vector< int > > CombinationsSet;
        typedef std::vector<int> CombinationSequence;

        bool belongsTo(const std::set<int>& currComb,const CombinationsSet& combs);

        bool enumeration(unsigned int listSize, unsigned int combSize, const CombinationsSet& checkV, Logger& logger);
        bool numElements(unsigned int listSize, unsigned int combSize, unsigned int checkV, Logger& logger);
        bool correcteness(Logger& logger);
    }
}

#endif //COMBINATIONS_CORRECTENESS_H
