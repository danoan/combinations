#ifndef SINGLE_COMBINATOR_H
#define SINGLE_COMBINATOR_H

#include <vector>
#include <stack>

#include "combinations/core/base/FundamentalCombinator.h"
#include "combinations/core/base/Event.h"
#include "combinations/core/base/Range.hpp"

#include "Resolver.h"

namespace Combinations
{
    namespace Core
    {
        namespace Single
        {
            template<class TRange>
            class Combinator
            {
            public:
                typedef TRange MyRange;
                typedef typename MyRange::IteratorType MyIterator;
                typedef Resolver<MyIterator> MyResolver;
                typedef FundamentalCombinator::Container Hops;

            public:
                Combinator(MyRange range) : range(range),
                                            fc(range.length, range.elemsPerComb)
                {
                    hops.resize(range.elemsPerComb);
                }

                bool next(MyResolver &resolver)
                {
                    bool flag = fc.next(hops);
                    resolver(range.begin, range.end, hops);

                    return flag;
                }

                void restart() { fc.restart(); }

                MyResolver resolver() { return MyResolver(); };

            public:
                MyRange range;
                FundamentalCombinator fc;
                Hops hops;
            };

            template<typename TRange>
            Combinator<TRange> createCombinator(TRange range)
            {
                return Combinator<TRange>(range);
            }

        }
    }
}



#endif
