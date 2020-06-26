#ifndef MAGLAC_LAB_UTILS_DISPLAYUTILS_H
#define MAGLAC_LAB_UTILS_DISPLAYUTILS_H

#include <iostream>
#include <vector>

namespace magLac {
namespace Utils {
/***
 * Prints a combination for each line
 * @param begin
 * @param end
 */
template<class TIterator>
void printCombinations(TIterator begin,
                       TIterator end,
                       std::ostream &os = std::cout);
}
}

#include "displayUtils.hpp"

#endif //MAGLAC_LAB_UTILS_DISPLAYUTILS_H
