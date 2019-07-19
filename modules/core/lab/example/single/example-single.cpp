#include <iostream>
#include <sstream>
#include <vector>

#include "combinations/core/base/Range.hpp"
#include "combinations/core/single/Combinator.hpp"
#include "combinations/utils/displayUtils.h"
#include "combinations/utils/mockUtils.h"
#include "combinations/logger/logger.h"

using namespace Combinations;
using namespace Combinations::Core;

typedef std::vector<int> IntVector;

template<class TResolver>
void cbf(std::vector<int>& nextComb,
        std::vector< std::vector<int> >& cv, 
        TResolver& resolver)
{
    resolver >> nextComb;
    cv.push_back(nextComb);
}

void highLoadExample(int n, int k)
{
    IntVector v = Utils::createIntegerVector(n);
    long int totalComb = 1;
    for(int i=0;i<k;++i) totalComb*=(n-i);
    for(int i=1;i<=k;++i) totalComb/=i;

    auto range = addRange(v.begin(),v.end(),k);
    auto combinator = Single::createCombinator(range);
    auto resolver = combinator.resolver();

    std::stringstream ss;
    Logger logger(ss,false);
    logger.startTimer();
    std::vector<int> nextComb(k);
    std::vector< std::vector<int> > cv;
    while(combinator.next(resolver))
    {
        cbf(nextComb,cv,resolver);
    }
    logger.endTimer();

//    Utils::printCombinations(cv.begin(),cv.end());

    std::cout << "Expected Combinations: " << totalComb << "\n";
    std::cout << "Computed Combinations: " << cv.size() << "\n\n";


    std::cout << "Execution Time: " << ss.str() << std::endl;
}

int main()
{
    highLoadExample(50,6);
    return 0;
}
