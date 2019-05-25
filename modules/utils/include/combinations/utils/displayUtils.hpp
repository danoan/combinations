#include "combinations/utils/displayUtils.h"

namespace Combinations
{
    namespace Utils
    {
        template<class TIterator>
        void printCombinations(TIterator begin,
                               TIterator end,
                               std::ostream& os)
        {
            for(auto itc=begin;itc!=end;++itc)
            {
                for(auto iti=itc->begin();iti!=itc->end();++iti)
                {
                    os << *iti << ",";
                }
                os << "\n";
            }
        }
    }
}
