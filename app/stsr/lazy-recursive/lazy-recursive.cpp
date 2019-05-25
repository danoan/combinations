#include <iostream>

#include "combinations/utils/mockUtils.h"
#include "combinations/single-range/lazy-recursive.h"

using namespace Combinations;

int main(int argc, char* argv[])
{
    if(argc<3)
    {
        std::cout << "\nUSAGE: lazy-recursive listSize combSize\n";
        exit(1);
    }

    unsigned long int listSize = std::atoi(argv[1]);
    unsigned long int combSize = std::atoi(argv[2]);

    auto intVector = Utils::createIntegerVector(listSize);
    auto combGenerator = LazyRecursive::combinations(combSize,
                                                     intVector.begin(),
                                                     intVector.end());

    typedef decltype(combGenerator) MyLazyCombinator;
    typedef MyLazyCombinator::CombinationSequence CombinationSequence;

    CombinationSequence curr;
    std::vector<CombinationSequence> cv;
    while(combGenerator.next(curr))
    {
        cv.push_back(curr);
    }

    std::cout << "\n Combinations count: " << cv.size() << "\n\n";


    return 0;
}