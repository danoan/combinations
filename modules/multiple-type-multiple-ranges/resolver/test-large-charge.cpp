#include <iostream>
#include <string>

#include "base/Range.hpp"
#include "multiple/Combinator.h"
#include "utils.h"


template<int numSets>
struct Charge
{
    typedef std::vector<IntVector> Sets;

    Charge()
    {
        for(int i=0;i<numSets;++i)
        {
            int nelems = rand()*10;
            sets.push_back(createIntegerVector(nelems));
        }
    }

    template<class TRange>
    auto _derive(TRange range, int index)
    {
        if(index<numSets)
            return _derive(range.addRange(sets[index].begin(),sets[index].end(),2));
        else
            return range;
    }

    auto derive()
    {
        return _derive(addRange(sets[0].begin(),sets[0].end(),2))
    }

    Sets sets;
};

int main()
{

    Charge<3> charge;


/*
    auto range = addRange(v1.begin(),v1.end(),2)
            .addRange(v2.begin(),v2.end(),2)
            .addRange(v3.begin(),v3.end(),2);

    auto mrc = Multiple::createCombinator(range);
*/

    return 0;
}
