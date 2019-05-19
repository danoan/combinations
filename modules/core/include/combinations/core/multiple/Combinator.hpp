#include "Combinator.h"

template<class TRange>
template<class TResolver>
void Combinator<TRange>::setResolver(TResolver &resolver)
{
    setResolver(resolver, 0);
}

template<class TRange>
template<class TResolver>
void Combinator<TRange>::setResolver(TResolver &resolver, Size proxyVectorIndex)
{

    if (proxyVectorIndex < numRanges) {
        resolver.set(fv[proxyVectorIndex].get());
        setResolver(resolver.previousSolver, proxyVectorIndex + 1);
    }

}

template<class TRange>
typename Combinator<TRange>::MyResolver Combinator<TRange>::resolver()
{
    return MyResolver(range);
}

template<class TRange>
Combinator<TRange>::Combinator(MyRange &range):
        range(range),
        numRanges(0)
{
    es.push(Event(Event::END, 0, 0));
    es.push(Event(Event::DIVE, 0, 0));

    initializeFundamentalVector(fv, range);
    numRanges = fv.size();
}

template<class TRange>
bool Combinator<TRange>::next(MyResolver &resolver)
{
    while (!es.empty())
    {
        Event e = es.top();
        es.pop();

        switch (e.action)
        {
            case Event::DIVE:
            {
                if (e.cIndex >= this->numRanges)
                {
                    es.push(Event(Event::DONE, e.cIndex, e.itMove));
                } else
                {
                    if (e.itMove != numRanges)
                    {
                        FundamentalCombinator &fc = fv[e.itMove];

                        if (fc.next()) {
                            es.push(Event(Event::BRANCH, e.cIndex, e.itMove));
                            es.push(Event(Event::DIVE, e.cIndex + 1, e.itMove + 1));
                        } else {
                            fc.restart();
                        }

                    }
                }

                break;
            }
            case Event::BRANCH:
            {
                es.push(Event(Event::DIVE, e.cIndex, e.itMove));
                break;
            }
            case Event::DONE:
            {
                setResolver(resolver);
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
