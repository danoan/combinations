#ifndef MULTIPLE_COMBINATOR_H
#define MULTIPLE_COMBINATOR_H

#include <vector>

#include "combinations/core/base/Range.hpp"
#include "combinations/core/base/Event.h"
#include "combinations/core/base/FundamentalCombinator.h"

#include "Resolver.h"

namespace Combinations
{
    namespace Core
    {
        namespace Multiple
        {
            template<class TRange>
            class Combinator
            {
            public:
                typedef TRange MyRange;
                typedef Resolver<MyRange, false> MyResolver; //assert that Range is composed of at least 2 ranges.
                typedef std::vector<FundamentalCombinator> FundamentalVector;

                typedef unsigned long int Size;

            private:
                typedef std::stack<Event> EventStack;

            public:
                Combinator(MyRange &range);

                bool next(MyResolver &resolver);

                MyResolver resolver();

            private:
                template<class TResolver>
                void setResolver(TResolver &resolver);

                template<class TResolver>
                void setResolver(TResolver &resolver, Size proxyVectorIndex);

            private:
                MyRange &range;
                FundamentalVector fv;

                Size numRanges;
                EventStack es;
            };


            template<class TRange>
            void initializeFundamentalVector(std::vector<FundamentalCombinator> &fv, const TRange &range)
            {
                fv.push_back(FundamentalCombinator(range.length, range.elemsPerComb));
                if (TRange::isFirst) return;
                else initializeFundamentalVector(fv, range.previous);
            }

            template<class TRange>
            Combinator<TRange> createCombinator(TRange &range)
            {
                return Combinator<TRange>(range);
            }

            #include "Combinator.hpp"
        }
    }
}

#endif
