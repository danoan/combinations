#ifndef COMBINATIONS_CORRECTENESS_H
#define COMBINATIONS_CORRECTENESS_H

#include <set>
#include <vector>

#include "combinations/core/base/Range.hpp"
#include "combinations/core/multiple/Resolver.h"
#include "combinations/logger/logger.h"

namespace Combinations
{
    namespace Test
    {
        typedef unsigned long int Size;
        typedef std::vector<int> IntVector;

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

#endif //COMBINATIONS_CORRECTENESS_H
