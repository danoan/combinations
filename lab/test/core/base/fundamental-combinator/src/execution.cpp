#include "magLac/lab/test/core/base/fundamental-combinator/execution.h"

namespace magLac
{
    namespace Test
    {
        namespace FundamentalCombinator
        {
            bool fundamentalCombinator(Size numElems, Size elemsPerComb,Logger& logger)
            {
                logger << Logger::HeaderTwo << "Test Execution" << Logger::Normal;
                logger << "Num. Elems:  " << numElems << "\n";
                logger << "Elems. per comb: " << elemsPerComb << "\n";

                bool flag = true;
                logger.startTimer();
                try{
                    Size totalComb = 1;

                    for(Size i=0;i<elemsPerComb;++i) totalComb*=(numElems-i);
                    for(Size i=1;i<=elemsPerComb;++i) totalComb/=i;

                    Core::FundamentalCombinator fc(numElems,elemsPerComb);
                    Core::FundamentalCombinator::Container nextComb;
                    int count=0;
                    while(fc.next(nextComb))count++;

                    logger << "Expected Combinations: " << totalComb << "\n";
                    logger << "Computed Combinations: " << count << "\n\n";
                }catch(std::exception& ex)
                {
                    logger << "Error: " << ex.what();
                    flag = false;
                }
                logger.endTimer();

                logger << "Passed: " << flag;

                return flag;
            }
            bool execution(Logger& logger)
            {
                bool flag=true;
                flag = flag && fundamentalCombinator(3,3,logger);
                flag = flag && fundamentalCombinator(10,3,logger);
                flag = flag && fundamentalCombinator(100,3,logger);
                flag = flag && fundamentalCombinator(100,5,logger);

                return flag;
            }
        }
    }
}