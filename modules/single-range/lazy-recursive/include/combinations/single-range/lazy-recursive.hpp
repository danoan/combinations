#include "lazy-recursive.h"

namespace Combinations
{
    namespace LazyRecursive
    {
        template<class TElementType, class TElementIterator>
        LazyCombinator<TElementType,TElementIterator>::
        LazyCombinator(Size combSize,
                       TElementIterator begin,
                       TElementIterator end):combSize(combSize),
                                             begin(begin),
                                             end(end),
                                             lastCombNum(0)
        {}

        template<class TElementType, class TElementIterator>
        bool LazyCombinator<TElementType,TElementIterator>::next(CombinationSequence& curr)
        {
            currCombNum = 0;
            curr.clear();
            if( rec_combinations(curr,this->combSize,begin,end)==SUCCESS )
            {
                ++this->lastCombNum;
                return true;
            }else{
                return false;
            }
        }

        template<class TElementType, class TElementIterator>
        typename LazyCombinator<TElementType,TElementIterator>::Status
        LazyCombinator<TElementType,TElementIterator>::rec_combinations(CombinationSequence& curr,
                                                                        Size k,
                                                                        TElementIterator begin,
                                                                        TElementIterator end)
        {
            if(k==0)
            {
                if(this->currCombNum==this->lastCombNum) return SUCCESS;
                else
                {
                    ++this->currCombNum;
                    return CONTINUE;
                }
            }

            if(begin==end) return FAILURE;

            while(begin!=end)
            {
                curr.push_back(*begin);
                ++begin;
                if( rec_combinations(curr,k-1,begin,end) == SUCCESS )
                {
                    return SUCCESS;
                }
                curr.pop_back();
            }

            return FAILURE;
        }
    }
}







