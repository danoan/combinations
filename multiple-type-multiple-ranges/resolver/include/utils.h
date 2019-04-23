#include <vector>
#include <iostream>

/***** Utility functions *****/
typedef std::vector<int> IntVector;
typedef std::vector<IntVector> CombinationsVector;
typedef CombinationsVector::const_iterator CombinationsIterator;

//Creates vector of integers with elements from 1..nelems
IntVector createIntegerVector(int nelems);

//Prints a combination for each line
template<class TIterator>
void printCombinations(TIterator begin, TIterator end)
{
    for(auto itc=begin;itc!=end;++itc)
    {
        for(auto iti=itc->begin();iti!=itc->end();++iti)
        {
            std::cout << *iti << ",";
        }
        std::cout << "\n";
    }

}
