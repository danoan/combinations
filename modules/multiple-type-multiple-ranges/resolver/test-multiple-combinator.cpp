#include <iostream>

#include "MultipleRangeCombinator.h"
#include "Range.hpp"
#include "utils.h"

template<typename TIteratorMaster, typename TIteratorSecond, typename... TIterators>
const bool Range<TIteratorMaster,TIteratorSecond,TIterators...>::isFirst = false;

template<typename TIteratorMaster, typename... TIterators>
const bool Range<TIteratorMaster,TIterators...>::isFirst = true;

int main()
{
    IntVector v = {1,2,3,4,5,6,7,8,9,10};

    auto b1 = v.begin();
    auto b2 = v.begin()+3;
    auto b3 = v.begin()+6;

    auto e1 = v.begin()+3;
    auto e2 = v.begin()+6;
    auto e3 = v.end();


    auto range = addRange(b1,e1,2).addRange(b2,e2,2).addRange(b3,e3,2);
    auto mrc = createMultipleRangeCombinator(range);

    IntVector c1(2);
    IntVector c2(2);
    IntVector c3(2);
    IntVector unionV;

    CombinationsVector cv;
    auto resolver = mrc.resolver();
    while(mrc.next(resolver))
    {
        std::cout << "Before Solve" << std::endl;
        resolver.solve(c1).solve(c2).solve(c3);
        std::cout << "After Solve" << std::endl;

        unionV.insert(unionV.end(),c1.begin(),c1.end());
        unionV.insert(unionV.end(),c2.begin(),c2.end());
        unionV.insert(unionV.end(),c3.begin(),c3.end());


        cv.push_back(unionV);
    }

    printCombinations(cv.begin(),cv.end());

    return 0;
}
