#ifndef MAGLAC_LAB_UTILS_MOCKUTILS_H
#define MAGLAC_LAB_UTILS_MOCKUTILS_H

#include <vector>

namespace magLac
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

#endif//MAGLAC_LAB_UTILS_MOCKUTILS_H