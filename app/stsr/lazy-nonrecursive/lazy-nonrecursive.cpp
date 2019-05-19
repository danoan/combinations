#include <iostream>

#include "combinations/utils/mockUtils.h"
#include "combinations/lazy-nonrecursive.h"

using namespace Combinations;

int main(int argc, char* argv[])
{
    if(argc<3)
    {
        std::cout << "\nUSAGE: lazy-nonrecursive listSize combSize\n";
        exit(1);
    }

    unsigned long int listSize = std::atoi(argv[1]);
    unsigned long int combSize = std::atoi(argv[2]);

    auto intVector = Utils::createIntegerVector(listSize);


    auto combGenerator = LazyNonRecursive::combinations(combSize,
                                                        intVector.begin(),
                                                        intVector.end());
    typedef decltype(combGenerator) MyLazyCombinator;
    typedef MyLazyCombinator::CombinationSequence CombinationSequence;
    
    std::vector<CombinationSequence> cv;
    CombinationSequence nextComb;
    while(combGenerator.next(nextComb))
    {
        cv.push_back(nextComb);
    }

    std::cout << "\n Combinations count: " << cv.size() << "\n\n";

    return 0;
}