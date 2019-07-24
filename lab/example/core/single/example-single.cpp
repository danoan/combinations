#include <iostream>
#include <sstream>
#include <vector>

#include "magLac/core/base/Range.hpp"
#include "magLac/core/single/Combinator.hpp"
#include "magLac/lab/utils/displayUtils.h"
#include "magLac/lab/utils/mockUtils.h"
#include "magLac/lab/logger/logger.h"

using namespace magLac;
using namespace magLac::Core;

typedef std::vector<int> IntVector;

int main(int argc, char* argv[])
{
    IntVector v = {1,2,3,4,5};
    unsigned long int elemsPerComb = 3;

    auto range = addRange(v.begin(),v.end(),elemsPerComb);
    auto combinator = Single::createCombinator(range);
    auto resolver = combinator.resolver();

    std::vector<int> nextComb(elemsPerComb);
    std::vector< std::vector<int> > cv;
    while(combinator.next(resolver))
    {
        resolver >> nextComb;
        cv.push_back(nextComb);
    }

    Utils::printCombinations(cv.begin(),cv.end());

    return 0;
}
