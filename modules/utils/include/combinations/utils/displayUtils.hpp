#include "combinations/utils/displayUtils.h"

namespace Combinations
{
    namespace Utils
    {
        template<class TElementType>
        void printCombinations(CombinationsIterator<TElementType> begin,
                               CombinationsIterator<TElementType> end)
        {
            for(auto itc=begin;itc!=end;++itc)
            {
                for(auto iti=itc->begin();iti!=itc->end();++iti)
                {
                    std::cout << *iti << ",";
                }
                std::cout << "\n";
            }
        }
    }
}
