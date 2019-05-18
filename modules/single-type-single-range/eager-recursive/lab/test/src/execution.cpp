#include "execution.h"

namespace Combinations
{
    namespace Test
    {
        bool execution(unsigned int listSize, unsigned int combSize, Logger& logger)
        {
            logger.startTimer();
            bool flag = false;
            try
            {
                logger < Logger::HeaderTwo < "Test Execution" < Logger::Normal;
                logger < "List Size: "  < listSize < "\n";
                logger < "Comb Size: "  < combSize < "\n";

                auto intVector = Utils::createIntegerVector(listSize);
                EagerRecursive::CombinationsVector<int> cv = EagerRecursive::combinations<int>(combSize,
                                                                                               intVector.begin(),
                                                                                               intVector.end());

                logger < "Combinations Counts: " < cv.size() < "\n";
                flag = true;
            }catch(std::exception ex)
            {
                logger < "Error: " < ex.what() < "\n";
                flag = false;
            }

            logger.endTimer();
            return flag;
        }
    }
}