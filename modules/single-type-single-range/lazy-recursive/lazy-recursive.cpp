#include <random>
#include <iostream>


/***** Core functions *****/
class Combinations
{
public:
  typedef std::vector<int> IntVector;
  typedef std::vector<IntVector> CombinationsVector;
  typedef IntVector::const_iterator IntIterator;
  typedef CombinationsVector::const_iterator CombinationsIterator;

  typedef unsigned long int Size;
  typedef char Status;

public:
  static const char CONTINUE=2;
  static const char SUCCESS=1;
  static const char FAILURE=0;

public:
  Combinations(Size combSize,
	       IntIterator begin,
	       IntIterator end);

  bool next(IntVector& curr);

private:

  Status rec_combinations(IntVector& curr,
			  Size k,
			  IntIterator begin,
			  IntIterator end);


private:
  Size combSize;
  IntIterator begin,end;
  Size lastCombNum;
  Size currCombNum;
};


/***** Utility functions *****/
Combinations::IntVector createIntegerVector(int nelems);
void printCombinations(Combinations::CombinationsIterator begin,
		       Combinations::CombinationsIterator end);


/***** Implementation *****/
Combinations::IntVector createIntegerVector(int nelems)
{
  Combinations::IntVector intVector;
  int x=1;
  while(nelems>0)
  {
    intVector.push_back(x++);
    --nelems;
  }

  return intVector;

}

void printCombinations(Combinations::CombinationsIterator begin,
		       Combinations::CombinationsIterator end)
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



Combinations::Combinations(Size combSize,
			   IntIterator begin,
			   IntIterator end):combSize(combSize),
					    begin(begin),
					    end(end),
					    lastCombNum(0)
{}

bool Combinations::next(IntVector& curr)
{
    currCombNum = 0;
    curr.clear();
    if( rec_combinations(curr,this->combSize,begin,end)==SUCCESS )
    {
      ++this->lastCombNum;
      return true;
    }else{
      return false;
    }
}

Combinations::Status Combinations::rec_combinations(IntVector& curr,
						    Size k,
						    IntIterator begin,
						    IntIterator end)
{
    if(k==0)
    {
      if(this->currCombNum==this->lastCombNum) return SUCCESS;
      else
      {
	++this->currCombNum;
	return CONTINUE;
      }
    }

    if(begin==end) return FAILURE;

    while(begin!=end)
    {
      curr.push_back(*begin);
      ++begin;
      if( rec_combinations(curr,k-1,begin,end) == SUCCESS )
      {
	  return SUCCESS;
      }
      curr.pop_back();
    }
}




int main(int argc, char* argv[])
{
  if(argc<3)
  {
    std::cout << "\nUSAGE: lazy-recursive listSize combSize\n";
    exit(1);
  }

  Combinations::Size listSize = std::atoi(argv[1]);
  Combinations::Size combSize = std::atoi(argv[2]);

  Combinations::IntVector intVector = createIntegerVector(listSize);


  Combinations combGenerator(combSize,
			     intVector.begin(),
			     intVector.end());

  Combinations::CombinationsVector cv;
  Combinations::IntVector curr;
  while(combGenerator.next(curr))
  {
    cv.push_back(curr);
  }

  std::cout << "\n Combinations count: " << cv.size() << "\n\n";


  return 0;
}
