#include <iostream>
#include <random>
#include <stack>
#include <vector>

/***** Core functions ******/

class Combinations
{
public:
  typedef unsigned long int Size;

private:
  struct Event
  {
    enum Action{DIVE,BRANCH,DONE,END};
    Event(Action action,Size cIndex,Size itMove):action(action),cIndex(cIndex),itMove(itMove){}

    Action action;
    Size cIndex;
    Size itMove;
  };

public:
  typedef std::vector<int> IntVector;
  typedef std::vector<IntVector> CombinationsVector;
  typedef IntVector::const_iterator IntIterator;
  typedef CombinationsVector::const_iterator CombinationsIterator;

  typedef std::stack<Event> EventStack;

private:
  inline IntIterator moveIt(IntIterator it, Size steps) const{ for(;steps>0;--steps) ++it; return it; }

public:
  Combinations(Size combSize, IntIterator begin, IntIterator end);
  bool next(IntVector& nextComb);

private:
  EventStack es;
  IntVector currComb;

  Size combSize;
  IntIterator begin,end;
};



/***** Utility functions *****/

//Creates vector of integers with elements from 1..nelems
Combinations::IntVector createIntegerVector(int nelems);

//Prints a combination for each line
void printCombinations(Combinations::CombinationsIterator begin,
		       Combinations::CombinationsIterator end);


/***** Implemention *****/

Combinations::IntVector createIntegerVector(int nelems)
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


Combinations::Combinations(Size combSize, IntIterator begin, IntIterator end):combSize(combSize),begin(begin),end(end)
{
  currComb.resize(combSize);
  es.push( Event(Event::END,0,0) );
  es.push( Event(Event::DIVE,0,0) );
}

bool Combinations::next(IntVector& nextComb)
{
  while(!es.empty())
  {
    Event e = es.top();
    es.pop();
    switch(e.action)
    {
      case Event::DIVE:
      {
	if(e.cIndex>=this->combSize)
	{
	  es.push( Event(Event::DONE, e.cIndex, e.itMove ) );
	}else
	{
	  IntIterator it = moveIt(begin,e.itMove);
	  if(it!=end)
	  {
	    currComb[e.cIndex] = *moveIt(begin,e.itMove);

	    es.push( Event(Event::BRANCH, e.cIndex, e.itMove) );
	    es.push( Event(Event::DIVE,e.cIndex+1,e.itMove+1) );
	  }
	}

	break;
      }
      case Event::BRANCH:
      {
	IntIterator it = moveIt(begin,e.itMove+1);
	if(it!=end)
	{
	  es.push( Event(Event::DIVE, e.cIndex, e.itMove+1) );
	}

	break;
      }
      case Event::DONE:
      {
	nextComb=currComb;
	return true;
      }
      case Event::END:
      {
	return false;
      }

    }
  }

  return false;
}



int main(int argc, char* argv[])
{
  if(argc<3)
  {
    std::cout << "\nUSAGE: lazy-nonrecursive listSize combSize\n";
    exit(1);
  }

  Combinations::Size listSize = std::atoi(argv[1]);
  Combinations::Size combSize = std::atoi(argv[2]);

  Combinations::IntVector intVector = createIntegerVector(listSize);


  Combinations combinations(combSize,
			    intVector.begin(),
			    intVector.end());

  Combinations::CombinationsVector cv;
  Combinations::IntVector nextComb;
  while(combinations.next(nextComb))
  {
    cv.push_back(nextComb);
  }

  std::cout << "\n Combinations count: " << cv.size() << "\n\n";

  return 0;
}
