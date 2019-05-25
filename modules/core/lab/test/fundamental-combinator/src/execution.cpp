#include "combinations/test/fundamental-combinator/execution.h"

namespace Combinations
{
    namespace Test
    {
        bool fundamentalCombinator(Size numElems, Size elemsPerComb,Logger& logger)
        {
            logger < Logger::HeaderTwo < "Test Execution" < Logger::Normal;
            logger < "Num. Elems: " < numElems < "\n";
            logger < "Elems. per comb: " < elemsPerComb < "\n";

            logger.startTimer();
            bool flag = true;
            try{
                Core::FundamentalCombinator fc(numElems,elemsPerComb);
                Core::FundamentalCombinator::Container nextComb;
                int count=0;
                while(fc.next(nextComb))count++;
            }catch(std::exception ex)
            {
                logger < "Error: " < ex.what();
                flag = false;
            }

            logger.endTimer();

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