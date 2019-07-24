#include "eager-recursive.h"

namespace magLac
{
    namespace EagerRecursive
    {
        template<class TElementType, class TElementIterator>
        Status rec_combinations(CombinationsVector<TElementType>& combs,
                                std::vector<TElementType>& curr,
                                Size k,
                                TElementIterator begin,
                                TElementIterator end)
        {
            if(k==0)
            {
                combs.push_back(curr);
                return SUCCESS;
            }

            if(begin==end) return FAILURE;

            while(begin!=end)
            {
                curr.push_back(*begin);
                ++begin;
                rec_combinations(combs,curr,k-1,begin,end);
                curr.pop_back();
            }

            return FAILURE;

        }

        template<class TElementType,class TElementIterator>
        CombinationsVector<TElementType> combinations(Size k, TElementIterator begin, TElementIterator end)
        {
            CombinationsVector<TElementType> combs;
            std::vector<TElementType> curr;
            rec_combinations(combs,curr,k,begin,end);

            return combs;
        }
    }
}




