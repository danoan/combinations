#ifndef COMBINATIONS_CORRECTENESS_H
#define COMBINATIONS_CORRECTENESS_H

#include <vector>
#include <set>

#include "combinations/logger/logger.h"
#include "combinations/core/base/FundamentalCombinator.h"
#include "combinations/utils/displayUtils.h"

namespace Combinations
{
    namespace Test
    {
        typedef unsigned long int Size;
        typedef std::vector< std::vector<Size> > CombinationsContainer;
        typedef std::vector< std::set<Size> > CombinationsCheckContainer;

        bool belongsTo(const std::set<Size>& currComb,const CombinationsContainer& combs);
        bool fundamentalCombinator(Size numElems, Size elemsPerComb, const CombinationsCheckContainer& checkV, Logger& logger);
        bool correcteness(Logger& logger);
    }
}

#endif //COMBINATIONS_CORRECTENESS_H
