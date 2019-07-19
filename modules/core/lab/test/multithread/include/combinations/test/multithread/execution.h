#ifndef COMBINATIONS_EXECUTION_H
#define COMBINATIONS_EXECUTION_H

#include <vector>

#include "combinations/core/multithread/MultiThreadLC.h"
#include "combinations/core/multithread/ThreadInput.h"
#include "combinations/core/multithread/ThreadControl.h"

#include "combinations/core/single/Combinator.hpp"

#include "combinations/logger/logger.h"
#include "combinations/utils/mockUtils.h"

namespace Combinations
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
