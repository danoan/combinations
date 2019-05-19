#include "correcteness.h"

namespace Combinations
{
    namespace Test
    {
        bool numElements(unsigned int listSize, unsigned int combSize, unsigned int checkV, Logger& logger)
        {
            logger < Logger::HeaderTwo < "Test Correcteness" < Logger::Normal;

            auto intVector = Utils::createIntegerVector(listSize);
            EagerRecursive::CombinationsVector<int> cv = EagerRecursive::combinations<int>(combSize,
                                                                                           intVector.begin(),
                                                                                           intVector.end());

            bool flag = cv.size()==checkV;
            logger < "ListSize: " < listSize < "\n";
            logger < "CombSize: " < combSize < "\n";
            logger < "Passed: " < flag < "\n";
            return flag;
        }

        bool belongsTo(const std::set<int>& currComb,const EagerRecursive::CombinationsVector<int>& combs)
        {
            for(auto itU=combs.begin();itU!=combs.end();++itU)
            {
                bool found = true;
                for(auto it=itU->begin();it!=itU->end();++it)
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

        bool enumeration(unsigned int listSize, unsigned int combSize, EagerRecursive::CombinationsVector<int> checkV, Logger& logger)
        {
            logger < Logger::HeaderTwo < "Test Correcteness" < Logger::Normal;

            auto intVector = Utils::createIntegerVector(listSize);
            EagerRecursive::CombinationsVector<int> cv = EagerRecursive::combinations<int>(combSize,
                                                                                           intVector.begin(),
                                                                                           intVector.end());

            bool flag=true;
            std::set<int> currComb;
            for(auto itS=checkV.begin();itS!=checkV.end();++itS)
            {
                currComb.clear();
                currComb.insert(itS->begin(),itS->end());

                if( belongsTo(currComb,cv)==false )
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

                EagerRecursive::CombinationsVector<int> cv = { {1,2},{1,3},{1,4},{2,3},{2,4},{3,4} };
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
