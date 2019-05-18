#include <vector>
#include <iostream>

/***** Utility functions *****/
typedef std::vector<int> IntVector;
typedef std::vector<IntVector> CombinationsVector;
typedef CombinationsVector::const_iterator CombinationsIterator;

//Creates vector of integers with elements from 1..nelems
IntVector createIntegerVector(int nelems);

//Prints a combination for each line
void printCombinations(CombinationsIterator begin,CombinationsIterator end);
