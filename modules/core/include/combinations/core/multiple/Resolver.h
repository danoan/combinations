#ifndef MULTIPLE_RESOLVER_H
#define MULTIPLE_RESOLVER_H

#include "combinations/core/single/Resolver.h"

namespace Combinations
{
    namespace Core
    {
        namespace Multiple {
            template<class TRange, bool= TRange::isFirst>
            class Resolver
            {
            };

            template<class TRange>
            class Resolver<TRange, true>
            {
            public:
                typedef unsigned long int Size;
                typedef std::vector<Size> VectorOfHops;

                typedef Resolver<TRange, true> Self;

            public:
                Resolver(TRange &range) : range(range), previousSolver(*this) {};

                void set(const VectorOfHops &hops) { this->hops = hops; }

                template<typename TContainer>
                void operator>>(TContainer &container)
                {
                    auto sr = Single::createResolver(range.begin);
                    sr(range.begin, range.end, hops);
                    sr >> container;
                }

            public:
                TRange range;
                VectorOfHops hops;

                Self &previousSolver;
            };


            template<class TRange>
            class Resolver<TRange, false>
            {
            public:
                typedef unsigned long int Size;
                typedef std::vector<Size> VectorOfHops;

                typedef typename TRange::PreviousRange PreviousRange;
                typedef Resolver<PreviousRange, PreviousRange::isFirst> PreviousSolver;

            public:
                Resolver(TRange &range) : range(range),
                                          previousSolver(PreviousSolver(range.previous)) {}

                void set(const VectorOfHops &hops) { this->hops = hops; }

                template<typename TContainer>
                PreviousSolver& operator>>(TContainer &container)
                {
                    auto sr = Single::createResolver(range.begin);
                    sr(range.begin, range.end, hops);
                    sr >> container;

                    return previousSolver;
                }

            public:
                TRange range;
                VectorOfHops hops;

                PreviousSolver previousSolver;
            };

            template<class TRange>
            Resolver<TRange> createResolver(TRange &range)
            {
                return Resolver<TRange>(range);
            }
        }
    }
}
#endif
