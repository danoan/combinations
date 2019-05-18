#include "combinations/utils/mockUtils.h"

namespace Combinations
{
    namespace Utils
    {
        IntVector createIntegerVector(int nelems)
        {
            std::vector<int> intVector;
            int x=1;
            while(nelems>0)
            {
                intVector.push_back(x++);
                --nelems;
            }

            return intVector;
        }
    }
}