#ifndef COMBINATIONS_DISPLAYUTILS_H
#define COMBINATIONS_DISPLAYUTILS_H

#include <iostream>
#include <vector>

namespace magLac
{
    namespace Utils
    {
        /***
         * Prints a combination for each line
         * @param begin
         * @param end
         */
        template<class TIterator>
        void printCombinations(TIterator begin,
                               TIterator end,
                               std::ostream& os=std::cout);
    }
}

#include "displayUtils.hpp"

#endif //COMBINATIONS_DISPLAYUTILS_H
