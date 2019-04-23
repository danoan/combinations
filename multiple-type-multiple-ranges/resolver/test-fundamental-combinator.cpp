#include "base/FundamentalCombinator.h"
#include "utils.h"

int main()
{
    FundamentalCombinator fc(5,3);

    FundamentalCombinator::Container nextComb;
    std::vector<FundamentalCombinator::Container> cv;
    while(fc.next(nextComb))
    {
        cv.push_back(nextComb);
    }

    printCombinations(cv.begin(),cv.end());
    return 0;
}