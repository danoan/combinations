#ifndef FUNDAMENTALCOMBINATOR_H
#define FUNDAMENTALCOMBINATOR_H

#include <vector>
#include <stack>

#include "Event.h"

namespace Combinations
{
    namespace Core
    {
        class FundamentalCombinator
        {
        public:
            typedef unsigned long int Size;
            typedef std::vector<Size> Container;

        private:
            typedef std::stack<Event> EventStack;

        public:
            FundamentalCombinator(Size numElements,
                                  Size elemsPerComb) : numElements(numElements),
                                                       elemsPerComb(elemsPerComb)
            {
                currCombination.resize(elemsPerComb);
                es.push(Event(Event::END, 0, 0));
                es.push(Event(Event::DIVE, 0, 0));
            }

            void restart()
            {
                es.push(Event(Event::END, 0, 0));
                es.push(Event(Event::DIVE, 0, 0));
            }

            bool next(Container &container)
            {
                bool flag = next();
                if (flag) container = currCombination;

                return flag;
            }

            bool next()
            {
                while (!es.empty())
                {
                    Event e = es.top();
                    es.pop();
                    switch (e.action)
                    {
                        case Event::DIVE:
                        {
                            if (e.cIndex >= elemsPerComb)
                            {
                                es.push(Event(Event::DONE, e.cIndex, e.itMove));
                            } else
                            {
                                if (e.itMove != numElements)
                                {
                                    currCombination[e.cIndex] = e.itMove;

                                    es.push(Event(Event::BRANCH, e.cIndex, e.itMove));
                                    es.push(Event(Event::DIVE, e.cIndex + 1, e.itMove + 1));
                                }
                            }

                            break;
                        }
                        case Event::BRANCH:
                        {
                            if ((e.itMove + 1) != numElements)
                            {
                                es.push(Event(Event::DIVE, e.cIndex, e.itMove + 1));
                            }

                            break;
                        }
                        case Event::DONE:
                        {
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

            const Container &get() { return currCombination; }

        public:
            Size numElements;
            Size elemsPerComb;

            EventStack es;
            Container currCombination;
        };
    }
}
#endif //MULTIPLE_RANGES_GENERAL_FUNDAMENTALCOMBINATOR_H
