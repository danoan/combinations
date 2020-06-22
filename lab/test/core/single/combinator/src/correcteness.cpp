#include "magLac/lab/test/core/single/combinator/correcteness.h"

namespace std
{
    template<>
    struct hash<magLac::Test::SingleCombinator::Element>
    {
        std::size_t operator()(const magLac::Test::SingleCombinator::Element& e) const noexcept
        {
            return std::hash<std::string>{}(e.e1[0]);
        }

    };

}

namespace magLac
{
    namespace Test
    {
        namespace SingleCombinator
        {
            CombinationSet expectedCS()
            {
                CombinationSet cs;
                cs.insert( Element({"Glasses","Cards"}) );
                cs.insert( Element({"Glasses","Bottles"}) );
                cs.insert( Element({"Glasses","Folders"}) );
                cs.insert( Element({"Cards","Bottles"}) );
                cs.insert( Element({"Cards","Folders"}) );
                cs.insert( Element({"Bottles","Folders"}) );

                return cs;
            }

            bool correcteness(Logger& logger)
            {
                using namespace magLac::Core;

                logger << Logger::HeaderTwo << "Test Correcteness" << Logger::Normal;

                StringVector v1 = {"Glasses","Cards","Bottles","Folders"};

                auto range = addRange(v1.begin(),v1.end(),2);

                auto combinator = createCombinator(range);
                auto resolver = combinator.resolver();

                StringVector c1(2);
                std::vector<Element> combinationSet;
                while(combinator.next(resolver))
                {
                    resolver >> c1;
                    combinationSet.push_back( c1 );
                }

                bool flag = true;
                CombinationSet checkCS = expectedCS();
                for(auto it=combinationSet.begin();it!=combinationSet.end();++it)
                {
                    if( checkCS.find(*it)==checkCS.end() )
                    {
                        flag = false;
                        break;
                    }
                }

                for(auto x:combinationSet) std::cout << x << "\n";

                flag = flag && checkCS.size()==combinationSet.size();

                logger << "Passed: " << flag;
                return flag;
            }

            std::ostream& operator<<(std::ostream& os, const Element& e)
            {
                for( auto x: e.e1) os << x << ",";

                return os;
            }
        }
    }
}