#include <iostream>
#include <combinations/single-range/eager-recursive.h>

#include "combinations/utils/displayUtils.h"
#include "combinations/utils/mockUtils.h"

#include "combinations/single-range/eager-recursive.h"

using namespace Combinations;

int main(int argc, char* argv[])
{
    if(argc<3)
    {
        std::cout << "\nUSAGE: eager-recursive listSize combSize\n";
        exit(1);
    }

    unsigned int listSize = std::atoi(argv[1]);
    unsigned int combSize = std::atoi(argv[2]);

    auto intVector = Utils::createIntegerVector(listSize);
    EagerRecursive::CombinationsVector<int> cv = EagerRecursive::combinations<int>(combSize,
                                                                                   intVector.begin(),
                                                                                   intVector.end());

    std::cout << "\n Combinations count: " << cv.size() << "\n\n";

    return 0;
}
