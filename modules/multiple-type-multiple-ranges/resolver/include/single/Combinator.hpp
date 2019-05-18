#ifndef SINGLE_COMBINATOR_H
#define SINGLE_COMBINATOR_H

#include <vector>
#include <stack>

#include "base/FundamentalCombinator.h"
#include "base/Event.h"
#include "base/Range.hpp"

#include "Resolver.h"

namespace Single {
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
        FundamentalCombinator fc;
        Hops hops;
        MyRange range;
    };

    template<typename TRange>
    Combinator<TRange> createCombinator(TRange range)
    {
        return Combinator<TRange>(range);
    }
}

#include "Combinator.hpp"

#endif
