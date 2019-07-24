#include "correcteness.h"

namespace magLac
{
    namespace Test
    {
        bool numElements(unsigned int listSize, unsigned int combSize, unsigned int checkV, Logger& logger)
        {
            logger < Logger::HeaderTwo < "Test Correcteness" < Logger::Normal;

            auto intVector = Utils::createIntegerVector(listSize);
            auto combGenerator = LazyNonRecursive::combinations(combSize,
                                                             intVector.begin(),
                                                             intVector.end());

            typedef decltype(combGenerator) MyLazyCombinator;
            typedef MyLazyCombinator::CombinationSequence CombinationSequence;

            unsigned long int size=0;
            CombinationSequence cs;
            while(combGenerator.next(cs)) ++size;

            bool flag = size==checkV;
            logger < "ListSize: " < listSize < "\n";
            logger < "CombSize: " < combSize < "\n";
            logger < "Passed: " < flag < "\n";
            return flag;
        }

        bool belongsTo(const std::set<int>& currComb,const CombinationsSet& combs)
        {
            for(auto itU=combs.cbegin();itU!=combs.cend();++itU)
            {
                bool found = true;
                for(auto it=itU->cbegin();it!=itU->cend();++it)
                {
                    if(currComb.find(*it)==currComb.end())
                    {
                        found=false;
                        break;
                    }
                }

                if(found) return true;
            }

            return false;
        }

        bool enumeration(unsigned int listSize, unsigned int combSize, const CombinationsSet& checkV, Logger& logger)
        {
            logger < Logger::HeaderTwo < "Test Correcteness" < Logger::Normal;

            auto intVector = Utils::createIntegerVector(listSize);
            auto combGenerator = LazyNonRecursive::combinations(combSize,
                                                             intVector.begin(),
                                                             intVector.end());

            typedef decltype(combGenerator) MyLazyCombinator;
            typedef MyLazyCombinator::CombinationSequence CombinationSequence;

            bool flag=true;
            std::set<int> currCombSet;
            CombinationSequence currComb;
            while(combGenerator.next(currComb))
            {
                currCombSet.clear();
                currCombSet.insert(currComb.begin(),currComb.end());

                if( belongsTo(currCombSet,checkV)==false )
                {
                    flag = false;
                    break;
                }
            }


            logger < "ListSize: " < listSize < "\n";
            logger < "CombSize: " < combSize < "\n";
            logger < "Passed: " < flag < "\n";

            return flag;
        }

        bool correcteness(Logger& logger)
        {
            bool flag = true;
            try
            {

                flag = flag && numElements(10,3,120,logger);
                flag = flag && numElements(3,3,1,logger);
                flag = flag && numElements(3,10,0,logger);

                CombinationsSet cv = { {1,2},{1,3},{1,4},{2,3},{2,4},{3,4} };
                flag = flag && enumeration(4,2,cv,logger);

            }catch(std::exception ex)
            {
                flag = false;
                logger < "Error: " < ex.what() < "\n\n";
            }

            return flag;
        }
    }

}
