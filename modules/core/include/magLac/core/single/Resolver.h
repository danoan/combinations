#ifndef SINGLE_RESOLVER_H
#define SINGLE_RESOLVER_H

#include <stdexcept>
#include <vector>

namespace magLac
{
    namespace Core
    {
        namespace Single
        {
            template<class TIterator>
            class Resolver
            {
            public:
                typedef TIterator Iterator;
                typedef unsigned long int Size;
                typedef std::vector<Size> VectorOfHops;

            private:
                TIterator moveIt(TIterator start, Size hops)
                {
                    for (Size i = 0; i < hops; ++i) ++start;
                    return start;
                }

            public:
                Resolver() {}

                void operator()(TIterator begin, TIterator end, VectorOfHops &hops)
                {
                    this->begin = begin;
                    this->end = end;
                    this->hops = hops;
                    this->flagIsValid = true;
                }

                template<class TContainer>
                Resolver &operator>>(TContainer &container)
                {
                    if (!flagIsValid) throw std::runtime_error("Resolver is exhausted!");

                    Size pos = 0;
                    for (auto it = hops.begin(); it != hops.end(); ++it, ++pos)
                    {
                        container[pos] = *moveIt(begin, *it);
                    }
                    flagIsValid = false;

                    return *this;
                }

            private:
                TIterator begin;
                TIterator end;
                VectorOfHops hops;

                bool flagIsValid;
            };

            template<typename TIterator>
            Resolver<TIterator> createResolver(TIterator begin)
            {

                return Resolver<TIterator>();
            }
        }
    }
}


#endif
