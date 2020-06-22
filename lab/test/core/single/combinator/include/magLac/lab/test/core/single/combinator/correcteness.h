#ifndef MAGLAC_LAB_TEST_CORE_SINGLE_COMBINATOR_CORRECTENESS_H
#define MAGLAC_LAB_TEST_CORE_SINGLE_COMBINATOR_CORRECTENESS_H

#include <vector>
#include <unordered_set>
#include <string>

#include "magLac/lab/logger/logger.h"
#include "magLac/core/base/Range.hpp"
#include "magLac/core/base/Combinator.h"

namespace magLac
{
    namespace Test
    {
        namespace SingleCombinator
        {
            typedef std::vector<std::string> StringVector;

            struct Element
            {
                Element(const StringVector &e1) : e1(e1) {}

                bool operator==(const Element& other) const
                {
                    return other.e1==e1;
                }

                friend std::ostream& operator<<(std::ostream& os, const Element& e);

                StringVector e1;
            };

            typedef std::unordered_set<Element> CombinationSet;
            CombinationSet expectedCS();

            bool correcteness(Logger& logger);
        }
    }
}

#endif //MAGLAC_LAB_TEST_CORE_SINGLE_COMBINATOR_CORRECTENESS_H

