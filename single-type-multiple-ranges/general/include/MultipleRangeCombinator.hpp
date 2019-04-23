#include "MultipleRangeCombinator.h"

template<class TType>
MultipleRangeCombinator<TType>::MultipleRangeCombinator():numRanges(0),
flagInitState(true)
{
  es.push( Event(Event::END,0,0) );
  es.push( Event(Event::DIVE,0,0) );
}

template<class TType>
void MultipleRangeCombinator<TType>::addRange(
  Size elemPerComb,
  MyVectorIterator begin,
   MyVectorIterator end)
{
  srcv.push_back( MyIndexableSingleRangeCombinator( this->numRanges++,
    MySingleRangeCombinator(elemPerComb,begin,end) ) );
}

template<class TType>
void MultipleRangeCombinator<TType>::addRange(MyVectorIterator begin,
  MyVectorIterator end)
{
  addRange(1,begin,end);
}

template<class TType>
bool MultipleRangeCombinator<TType>::next(MyVector& combVector)
{
  if(flagInitState)
  {
    currComb.init(srcv);
    flagInitState = false;
  }

  MySingleRangeCombinatorVectorIterator begin = srcv.begin();
  MySingleRangeCombinatorVectorIterator end = srcv.end();

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
      	  MySingleRangeCombinatorVectorIterator it = moveIt(begin,e.itMove);
      	  if(it!=end)
      	  {
            MySingleRangeCombinator& partialComb  = it->combinator;

            MyVector combSegment;
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
