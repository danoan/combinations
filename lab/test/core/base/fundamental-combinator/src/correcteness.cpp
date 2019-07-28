#include "magLac/lab/test/core/base/fundamental-combinator/correcteness.h"

namespace magLac
{
    namespace Test
    {
        namespace FundamentalCombinator
        {
            bool belongsTo(const std::set<Size>& currComb,const CombinationsContainer& combs)
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

            bool fundamentalCombinator(Size numElems, Size elemsPerComb, const CombinationsCheckContainer& checkV, Logger& logger)
            {
                logger << Logger::HeaderTwo << "Test correcteness" << Logger::Normal;
                logger << "Num. Elems:  " << numElems << "\n";
                logger << "Elems. per comb: " << elemsPerComb << "\n";

                Core::FundamentalCombinator fc(numElems,elemsPerComb);

                Core::FundamentalCombinator::Container nextComb;
                std::vector<Core::FundamentalCombinator::Container> cv;
                while(fc.next(nextComb))cv.push_back(nextComb);

                for(auto it=checkV.begin();it!=checkV.end();++it)
                {
                    if(!belongsTo(*it,cv))
                    {
                        logger << "Passed: false\n";

                        logger << "Computed: \n";
                        Utils::printCombinations(cv.begin(),cv.end(),logger.stream());

                        logger << "Expected: \n";
                        Utils::printCombinations(checkV.begin(),checkV.end(),logger.stream());
                        return false;
                    }
                }

                logger << "Passed: true\n";
                return true;

            }

            bool correcteness(Logger& logger)
            {
                bool flag=true;

                flag = flag && fundamentalCombinator(4, 2, { {0,1},{0,2},{0,3},{1,2},{1,3},{2,3} },logger);
                flag = flag && fundamentalCombinator(3, 3, { {0,1,2} },logger);

                return flag;
            }
        }

    }
}