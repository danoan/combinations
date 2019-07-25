#ifndef MAGLAC_CORE_BASE_RANGE_H
#define MAGLAC_CORE_BASE_RANGE_H

namespace magLac
{
    namespace Core
    {
        template<typename TIteratorMaster, typename... TIterators>
        struct Range
        {
            typedef unsigned long int Size;
            typedef TIteratorMaster IteratorType;

            typedef Range<TIteratorMaster, TIterators...> Self;

            Range(TIteratorMaster begin, TIteratorMaster end, Size elemsPerComb) :
                    begin(begin),
                    end(end),
                    elemsPerComb(elemsPerComb),
                    length(0),
                    previous(*this)
            {
                for (auto it = begin; it != end; ++it, ++length);
            }

            template<class TIteratorNext>
            Range<TIteratorNext, TIteratorMaster> addRange(TIteratorNext begin,
                                                           TIteratorNext end, Size elemsPerComb)
            {
                return Range<TIteratorNext, TIteratorMaster>(*this, begin, end, elemsPerComb);
            }

            static const bool isFirst;

            TIteratorMaster begin;
            TIteratorMaster end;
            Size elemsPerComb;
            Size length;

            Self &previous; //Mock for initializeProxyVector in MultipleRangeCombinator.h
        };

        template<typename TIteratorMaster, typename TIteratorSecond, typename... TIterators>
        struct Range<TIteratorMaster, TIteratorSecond, TIterators...>
        {
            typedef unsigned long int Size;
            typedef TIteratorMaster IteratorType;

            typedef Range<TIteratorMaster, TIteratorSecond, TIterators...> Self;
            typedef Range<TIteratorSecond, TIterators...> PreviousRange;

            Range(const PreviousRange &previous,
                  TIteratorMaster begin, TIteratorMaster end, Size elemsPerComb) :
                    begin(begin), end(end), elemsPerComb(elemsPerComb),length(0),previous(previous)
            {
                for (auto it = begin; it != end; ++it, ++length);
            }

            template<class TIteratorNext>
            Range<TIteratorNext, TIteratorMaster, TIteratorSecond, TIterators...>
            addRange(TIteratorNext begin, TIteratorNext end, Size elemsPerComb)
            {
                return Range<TIteratorNext, TIteratorMaster, TIteratorSecond, TIterators...>(*this, begin, end, elemsPerComb);
            }


            TIteratorMaster begin;
            TIteratorMaster end;
            Size elemsPerComb;
            Size length;

            PreviousRange previous;
            static const bool isFirst;
        };

        template<typename TIterator>
        Range<TIterator> addRange(TIterator begin, TIterator end, unsigned long int elemsPerComb)
        {
            return Range<TIterator>(begin, end, elemsPerComb);
        }

        template<typename TIteratorMaster, typename TIteratorSecond, typename... TIterators>
        const bool Range<TIteratorMaster,TIteratorSecond,TIterators...>::isFirst = false;

        template<typename TIteratorMaster, typename... TIterators>
        const bool Range<TIteratorMaster,TIterators...>::isFirst = true;
    }
}

#endif//MAGLAC_CORE_BASE_RANGE_H
