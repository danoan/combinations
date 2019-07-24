#ifndef COMBINATIONS_LAZY_NONRECURSIVE_H
#define COMBINATIONS_LAZY_NONRECURSIVE_H

#include <stack>
#include <vector>

#include "Event.h"

namespace magLac
{
    namespace LazyNonRecursive
    {
        template<class TElementType,class TElementIterator>
        class LazyCombinator
        {
        public:
            typedef std::vector<TElementType> CombinationSequence;
            typedef unsigned long int Size;

        private:
            typedef std::stack<Event> EventStack;

        private:
            inline TElementIterator moveIt(TElementIterator it, Size steps) const{ for(;steps>0;--steps) ++it; return it; }

        public:
            LazyCombinator(Size combSize, TElementIterator begin, TElementIterator end);
            bool next(CombinationSequence& nextComb);

        private:
            EventStack es;
            CombinationSequence currComb;

            Size combSize;
            TElementIterator begin,end;
        };

        template<class TElementIterator,class TElementType=typename TElementIterator::value_type>
        LazyCombinator<TElementType,TElementIterator> combinations(unsigned long int combSize,
                TElementIterator begin,
                TElementIterator end)
        {
            return LazyCombinator<TElementType,TElementIterator>(combSize,begin,end);
        }
    }
}

#include "lazy-nonrecursive.hpp"

#endif //COMBINATIONS_LAZY_NONRECURSIVE_H
