#include "lazy-nonrecursive.h"


namespace magLac
{
    namespace LazyNonRecursive
    {
        template<class TElementType,class TElementIterator>
        LazyCombinator<TElementType,TElementIterator>::LazyCombinator(Size combSize,
                                                                      TElementIterator begin,
                                                                      TElementIterator end):combSize(combSize),
                                                                                       begin(begin),
                                                                                       end(end)
        {
            currComb.resize(combSize);
            es.push( Event(Event::END,0,0) );
            es.push( Event(Event::DIVE,0,0) );
        }

        template<class TElementType,class TElementIterator>
        bool LazyCombinator<TElementType,TElementIterator>::next(CombinationSequence& nextComb)
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
                            TElementIterator it = moveIt(begin,e.itMove);
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
                        TElementIterator it = moveIt(begin,e.itMove+1);
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

    }
}





