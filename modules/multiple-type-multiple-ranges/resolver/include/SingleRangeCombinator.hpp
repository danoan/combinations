#include "SingleRangeCombinator.h"

template<class TRange>
typename SingleRangeCombinator<TRange>::MyResolver SingleRangeCombinator<TRange>::resolver()
{
  return MyResolver();
}

template<class TRange>
SingleRangeCombinator<TRange>::SingleRangeCombinator(MyRange range):
elemsPerComb(range.elemsPerComb),range(range)
{
  currHops.resize(elemsPerComb);
  es.push( Event(Event::END,0,0) );
  es.push( Event(Event::DIVE,0,0) );
}

template<class TRange>
void SingleRangeCombinator<TRange>::restart()
{
  es.push( Event(Event::END,0,0) );
  es.push( Event(Event::DIVE,0,0) );
}

template<typename TRange>
bool SingleRangeCombinator<TRange>::next(MyResolver& resolver)
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
      	  Size pos = e.itMove;
      	  if(pos!=range.length)
      	  {
      	    currHops[e.cIndex] = e.itMove;

      	    es.push( Event(Event::BRANCH, e.cIndex, e.itMove) );
      	    es.push( Event(Event::DIVE,e.cIndex+1,e.itMove+1) );
      	  }
      	}

    	   break;
      }
      case Event::BRANCH:
      {
      	Size pos = e.itMove+1;
      	if(pos!=range.length)
      	{
      	  es.push( Event(Event::DIVE, e.cIndex, e.itMove+1) );
      	}

	       break;
      }
      case Event::DONE:
      {
      	resolver(range.begin,range.end,currHops);
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
