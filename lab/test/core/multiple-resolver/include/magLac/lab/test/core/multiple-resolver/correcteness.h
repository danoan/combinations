#ifndef MAGLAC_LAB_TEST_CORE_MULTIPLERESOLVER_CORRECTENESS_H
#define MAGLAC_LAB_TEST_CORE_MULTIPLERESOLVER_CORRECTENESS_H

#include <set>
#include <vector>

#include "magLac/core/base/Range.hpp"
#include "magLac/core/multiple/Resolver.h"
#include "magLac/lab/logger/logger.h"

namespace magLac
{
    namespace Test
    {
        namespace MultipleResolver
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
}

#endif //MAGLAC_LAB_TEST_CORE_MULTIPLERESOLVER_CORRECTENESS_H
