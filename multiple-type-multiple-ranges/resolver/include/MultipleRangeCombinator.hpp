#include "MultipleRangeCombinator.h"

template<class TRange>
typename MultipleRangeCombinator<TRange>::MyResolver MultipleRangeCombinator<TRange>::resolver()
{
  return MyResolver(range);
}

template<class TRange>
MultipleRangeCombinator<TRange>::MultipleRangeCombinator(MyRange& range):
range(range),
numRanges(0)
{
  es.push( Event(Event::END,0,0) );
  es.push( Event(Event::DIVE,0,0) );

  initializeProxyVector(pv,range);
  numRanges = pv.size();
}

template<class TRange>
bool MultipleRangeCombinator<TRange>::next(MyResolver& resolver)
{
  while(!es.empty())
  {
    Event e = es.top();
    es.pop();

    switch(e.action)
    {
      case Event::DIVE:
      {
        std::cout << "Dive" << std::endl;
      	if(e.cIndex>=this->numRanges)
      	{
      	  es.push( Event(Event::DONE, e.cIndex, e.itMove ) );
      	}else
      	{
          Size pos = e.itMove;
      	  if(pos<numRanges)
      	  {
            Proxy& proxy = pv[e.itMove];
            auto resolver = proxy.resolver();

            if(proxy.combinator.next(resolver))
            {
              resolver >> proxy.currHops;

        	    es.push( Event(Event::BRANCH, e.cIndex, e.itMove) );
        	    es.push( Event(Event::DIVE,e.cIndex+1,e.itMove+1) );
            }else
            {
                proxy.combinator.restart();
            }

      	  }
      	}

    	   break;
      }
      case Event::BRANCH:
      {
        std::cout << "Branch" << std::endl;
      	es.push( Event(Event::DIVE, e.cIndex, e.itMove) );
	      break;
      }
      case Event::DONE:
      {
        std::cout << "Done" << std::endl;
        setResolver(resolver);
        return true;
      }
      case Event::END:
      {
        std::cout << "End" << std::endl;
         return false;
      }

    }
  }

  return false;
}
