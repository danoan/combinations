#ifndef MAGLAC_LAB_BENCHMARK_TECHNIQUES_LAZYNONRECURSIVE_LAB_TEST_CORRECTENESS_H
#define MAGLAC_LAB_BENCHMARK_TECHNIQUES_LAZYNONRECURSIVE_LAB_TEST_CORRECTENESS_H

#include <set>

#include "lazy-nonrecursive.h"

#include "magLac/lab/utils/mockUtils.h"
#include "magLac/lab/logger/logger.h"

namespace magLac
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

#endif //MAGLAC_LAB_BENCHMARK_TECHNIQUES_LAZYNONRECURSIVE_LAB_TEST_CORRECTENESS_H
