#ifndef COMBINATIONS_MOCK_UTILS
#define COMBINATIONS_MOCK_UTILS

#include <vector>

namespace Combinations
{
    namespace Utils
    {
        typedef std::vector<int> IntVector;

        /***
         * Creates vector of integers with elements from 1..nelems
         *
         * @param nelems Number of elements in the vector
         * @return A vector of integers
         */
        IntVector createIntegerVector(int nelems);


    }
}

#endif