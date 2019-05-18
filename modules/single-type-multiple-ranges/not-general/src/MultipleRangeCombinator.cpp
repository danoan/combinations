#include "MultipleRangeCombinator.h"

MultipleRangeCombinator::MultipleRangeCombinator():numRanges(0),flagInitState(true)
{
  es.push( Event(Event::END,0,0) );
  es.push( Event(Event::DIVE,0,0) );
}

void MultipleRangeCombinator::addRange(Size elemPerComb,
  IntIterator begin,
   IntIterator end)
{
  srcv.push_back( IndexableSingleRangeCombinator( this->numRanges++,
    SingleRangeCombinator(elemPerComb,begin,end) ) );
}

void MultipleRangeCombinator::addRange(IntIterator begin, IntIterator end)
{
  addRange(1,begin,end);
}

bool MultipleRangeCombinator::next(IntVector& combVector)
{
  if(flagInitState)
  {
    currComb.init(srcv);
    flagInitState = false;
  }

  SingleRangeCombinatorVectorIterator begin = srcv.begin();
  SingleRangeCombinatorVectorIterator end = srcv.end();

  while(!es.empty())
  {
    Event e = es.top();
    es.pop();

    switch(e.action)
    {
      case Event::DIVE:
      {
      	if(e.cIndex>=this->numRanges)
      	{
      	  es.push( Event(Event::DONE, e.cIndex, e.itMove ) );
      	}else
      	{
      	  SingleRangeCombinatorVectorIterator it = moveIt(begin,e.itMove);
      	  if(it!=end)
      	  {
            SingleRangeCombinator& partialComb  = it->combinator;

            IntVector combSegment;
            bool partialSuccess = partialComb.next(combSegment);

            if(partialSuccess)
            {
              currComb.update(*it,combSegment);

        	    es.push( Event(Event::BRANCH, e.cIndex, e.itMove) );
        	    es.push( Event(Event::DIVE,e.cIndex+1,e.itMove+1) );
            }else
            {
                partialComb.restart();
            }

      	  }
      	}

    	   break;
      }
      case Event::BRANCH:
      {
      	es.push( Event(Event::DIVE, e.cIndex, e.itMove) );
	      break;
      }
      case Event::DONE:
      {
        combVector = currComb();
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
