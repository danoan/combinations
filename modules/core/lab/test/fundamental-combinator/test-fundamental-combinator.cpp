#include "combinations/core/base/FundamentalCombinator.h"
#include "combinations/utils/displayUtils.h"

using namespace Combinations;
using namespace Combinations::MultipleRanges;

int main()
{
    FundamentalCombinator fc(5,3);

    FundamentalCombinator::Container nextComb;
    std::vector<FundamentalCombinator::Container> cv;
    while(fc.next(nextComb))
    {
        cv.push_back(nextComb);
    }

    Utils::printCombinations<unsigned long int>(cv.begin(),cv.end());
    return 0;
}