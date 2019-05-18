#ifndef COMBINATIONS_EAGER_RECURSIVE_H
#define COMBINATIONS_EAGER_RECURSIVE_H

#include <vector>

namespace Combinations
{
    namespace EagerRecursive
    {
        template<class T>
        using CombinationsVector = std::vector< std::vector<T> >;

        template<class TElementType>
        using CombinationsIterator = typename CombinationsVector<TElementType>::const_iterator;

        typedef unsigned long int Size;
        enum Status{FAILURE,SUCCESS,CONTINUE};

        /***
         * Computes all integer combinations of size k starting with *begin
         * @param combs
         * @param curr
         * @param k
         * @param begin
         * @param end
         * @return
         */
        template<class TElementType, class TElementIterator>
        Status rec_combinations(CombinationsVector<TElementType>& combs,
                                std::vector<TElementType>& curr,
                                Size k,
                                TElementIterator begin,
                                TElementIterator end);

        /***
         * Computes all combinations of size k for a list of integers
         * @param k
         * @param begin
         * @param end
         * @return
         */
        template<class TElementType,class TElementIterator>
        CombinationsVector<TElementType> combinations(Size k,
                                                      TElementIterator begin,
                                                      TElementIterator end);

    }
}

#include "eager-recursive.hpp"

#endif //COMBINATIONS_EAGER_RECURSIVE_H
