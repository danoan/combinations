#ifndef MAGLAC_LAB_TEST_CORE_MULTITHREAD_EXECUTION_H
#define MAGLAC_LAB_TEST_CORE_MULTITHREAD_EXECUTION_H

#include <vector>

#include "magLac/core/multithread/Trigger.h"
#include "magLac/core/multithread/ThreadInput.h"
#include "magLac/core/multithread/ThreadControl.h"
#include "magLac/core/base/Combinator.h"

#include "magLac/lab/logger/logger.h"
#include "magLac/lab/utils/mockUtils.h"

namespace magLac
{
    namespace Test
    {
        namespace Multithread
        {
            typedef unsigned long int Size;
            typedef std::vector<int> IntVector;

            struct ExecutionParams{};

            struct ExecutionUserVars
            {
                void restart(){};
                std::vector<IntVector> cv;
            };

            bool executionMultithread(Logger& logger,Size numThreads, Size n, Size k);
            bool execution(Logger& logger);
        }
    }
}

#endif //MAGLAC_LAB_TEST_CORE_MULTITHREAD_EXECUTION_H
