#ifndef MAGLAC_LAB_TEST_CORE_MULTIPLE_COMBINATOR_CORRECTENESS_H
#define MAGLAC_LAB_TEST_CORE_MULTIPLE_COMBINATOR_CORRECTENESS_H

#include <vector>
#include <unordered_set>
#include <string>

#include "magLac/magLac.h"
#include "magLac/lab/logger/logger.h"

namespace magLac
{
    namespace Test
    {
        namespace MultipleCombinator
        {
            typedef std::vector<int> IntVector;
            typedef std::vector<std::string> StringVector;

            struct Element
            {
                Element(const IntVector &e1, const StringVector &e2) : e1(e1), e2(e2) {}

                bool operator==(const Element& other) const
                {
                    return other.e1==e1 && other.e2==e2;
                }

                friend std::ostream& operator<<(std::ostream& os, const Element& e);

                IntVector e1;
                StringVector e2;
            };

            typedef std::unordered_set<Element> CombinationSet;
            CombinationSet expectedCS();

            bool correcteness(Logger& logger);
        }
    }
}

#endif //MAGLAC_LAB_TEST_CORE_MULTIPLE_COMBINATOR_CORRECTENESS_H
