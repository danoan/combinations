#include "combinations/test/range/correcteness.h"

using namespace Combinations::Core;

namespace Combinations
{
    namespace Test
    {

        bool correcteness(Logger& logger)
        {
            logger < Logger::HeaderTwo < "Test Correcteness" < Logger::Normal;

            std::vector<int> v = {1,2,3,4,5,6,7,8,9,10};
            auto b1 = v.begin();
            auto b2 = v.begin()+3;
            auto b3 = v.begin()+6;

            auto e1 = v.begin()+3;
            auto e2 = v.begin()+6;
            auto e3 = v.end();

            bool flag = true;

            auto R = addRange(b1,e1,2).addRange(b2,e2,2).addRange(b3,e3,2);
            flag = flag && check(R.begin,R.end, {7,8,9,10});

            auto previous = R.previous;
            flag = flag && check(previous.begin,previous.end,{4,5,6});

            auto previous2 = previous.previous;
            flag = flag && check(previous2.begin,previous2.end,{1,2,3});

            logger < "Passed: "  < flag;

            return flag;
        }
    }

}