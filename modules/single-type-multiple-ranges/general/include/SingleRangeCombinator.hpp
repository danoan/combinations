#include "SingleRangeCombinator.h"

template<class TType>
SingleRangeCombinator<TType>::SingleRangeCombinator(Size elemsPerComb,
  MyVectorIterator begin,
  MyVectorIterator end):elemsPerComb(elemsPerComb),begin(begin),end(end)
{
  currComb.resize(elemsPerComb);
  es.push( Event(Event::END,0,0) );
  es.push( Event(Event::DIVE,0,0) );
}

template<class TType>
void SingleRangeCombinator<TType>::restart()
{
  es.push( Event(Event::END,0,0) );
  es.push( Event(Event::DIVE,0,0) );
}

template<class TType>
bool SingleRangeCombinator<TType>::next(MyVector& nextComb)
{
  while(!es.empty())
  {
    Event e = es.top();
    es.pop();
    switch(e.action)
    {
      case Event::DIVE:
      {
      	if(e.cIndex>=elemsPerComb)
      	{
      	  es.push( Event(Event::DONE, e.cIndex, e.itMove ) );
      	}else
      	{
      	  MyVectorIterator it = moveIt(begin,e.itMove);
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
      	MyVectorIterator it = moveIt(begin,e.itMove+1);
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
