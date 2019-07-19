#ifndef COMBINATIONS_CORRECTENESS_H
#define COMBINATIONS_CORRECTENESS_H

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

        struct CorrectParams{};

        struct CorrectUserVars
        {
            void restart(){};
            std::vector<IntVector> cv;
        };

        bool correctenessMultithread(Logger& logger,Size numThreads, Size n, Size k);
        bool correcteness(Logger& logger);
    }
}


#endif //COMBINATIONS_CORRECTENESS_H
