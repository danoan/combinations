#include <random>
#include <iostream>

typedef std::vector<int> IntVector;
typedef std::vector<IntVector> CombinationsVector;
typedef IntVector::const_iterator IntIterator;
typedef CombinationsVector::const_iterator CombinationsIterator;

typedef unsigned long int Size;
typedef char Status;

#define CONTINUE 2
#define SUCCESS 1
#define FAILURE 0

/***** Utility functions *****/

//Creates vector of integers with elements from 1..nelems
IntVector createIntegerVector(int nelems);

//Prints a combination for each line
void printCombinations(CombinationsIterator begin,
		       CombinationsIterator end);


/***** Core functions  ******/

//Computes all integer combinations of size k starting with *begin
Status rec_combinations(CombinationsVector& combs,
			IntVector& curr,
			Size k,
			IntIterator begin,
			IntIterator end);

//Computes all combinations of size k for a list of integers
CombinationsVector combinations(Size k,
				IntIterator begin,
				IntIterator end);




/***** Implemention *****/

IntVector createIntegerVector(int nelems)
{
  std::vector<int> intVector;
  int x=1;
  while(nelems>0)
  {
    intVector.push_back(x++);
    --nelems;
  }

  return intVector;
}

void printCombinations(CombinationsIterator begin,
		       CombinationsIterator end)
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

Status rec_combinations(CombinationsVector& combs,
		      IntVector& curr,
		      Size k,
		      IntIterator begin,
		      IntIterator end)
{
  if(k==0)
  {
    combs.push_back(curr);
    return SUCCESS;
  }

  if(begin==end) return FAILURE;

  while(begin!=end)
  {
    curr.push_back(*begin);
    ++begin;
    rec_combinations(combs,curr,k-1,begin,end);
    curr.pop_back();
  }

}

CombinationsVector combinations(Size k, IntIterator begin, IntIterator end)
{
  CombinationsVector combs;
  IntVector curr;
  rec_combinations(combs,curr,k,begin,end);

  return combs;
}



int main(int argc, char* argv[])
{
  if(argc<3)
  {
    std::cout << "\nUSAGE: eager-recursive listSize combSize\n";
    exit(1);
  }

  Size listSize = std::atoi(argv[1]);
  Size combSize = std::atoi(argv[2]);

  IntVector intVector = createIntegerVector(listSize);


  CombinationsVector cv = combinations(combSize,
				       intVector.begin(),
				       intVector.end());

  std::cout << "\n Combinations count: " << cv.size() << "\n\n";


  return 0;
}
