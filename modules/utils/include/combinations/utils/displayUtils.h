#ifndef COMBINATIONS_DISPLAYUTILS_H
#define COMBINATIONS_DISPLAYUTILS_H

#include <iostream>
#include <vector>

namespace Combinations
{
    namespace Utils
    {
        template<class TElementType>
        using CombinationsVector = std::vector< std::vector<TElementType> >;

        template<class TElementType>
        using CombinationsIterator = typename CombinationsVector<TElementType>::const_iterator;

        /***
         * Prints a combination for each line
         * @param begin
         * @param end
         */
        template<class TElementType>
        void printCombinations(CombinationsIterator<TElementType> begin,
                               CombinationsIterator<TElementType> end);
    }
}

#include "displayUtils.hpp"

#endif //COMBINATIONS_DISPLAYUTILS_H
