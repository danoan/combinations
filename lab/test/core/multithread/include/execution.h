#ifndef COMBINATIONS_EXECUTION_H
#define COMBINATIONS_EXECUTION_H

#include <vector>

#include "magLac/core/multithread/MultiThreadLC.h"
#include "magLac/core/multithread/ThreadInput.h"
#include "magLac/core/multithread/ThreadControl.h"
#include "magLac/core/single/Combinator.hpp"

#include "magLac/lab/logger/logger.h"
#include "magLac/lab/utils/mockUtils.h"

namespace magLac
{
    namespace Test
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

#endif //COMBINATIONS_EXECUTION_H
