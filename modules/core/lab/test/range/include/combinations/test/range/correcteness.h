#ifndef COMBINATIONS_CORRECTION_H
#define COMBINATIONS_CORRECTION_H

#include <set>

#include "combinations/core/base/Range.hpp"
#include "combinations/logger/logger.h"

namespace Combinations
{
    namespace Test
    {
        template<class TIterator, class TValueType=typename TIterator::value_type>
        bool check(TIterator begin, TIterator end, const std::set<TValueType>& checkSet)
        {
            for(auto it=begin;it!=end;++it)
            {
                if( checkSet.find(*it)==checkSet.end() ) return false;
            }

            return true;
        }

        bool correcteness(Logger& logger);
    }
}

#endif //COMBINATIONS_CORRECTION_H
