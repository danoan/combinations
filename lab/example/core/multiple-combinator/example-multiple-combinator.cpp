#include <iostream>
#include <string>

#include "magLac/core/base/Range.hpp"
#include "magLac/core/base/Combinator.h"
#include "magLac/lab/utils/displayUtils.h"

using namespace magLac;
using namespace magLac::Core;

typedef std::vector<int> IntVector;
typedef std::vector<double> DoubleVector;
typedef std::vector<std::string> StringVector;

void singleType()
{
    IntVector v1 = {1,2,3};
    IntVector v2 = {4,5,6};
    IntVector v3 = {7,8,9,10};

    auto range = addRange(v1.begin(),v1.end(),2)
            .addRange(v2.begin(),v2.end(),2)
            .addRange(v3.begin(),v3.end(),2);

    auto mrc = createCombinator(range);

    IntVector c1(2),c2(2),c3(2),unionV;

    std::vector<IntVector> cv;
    auto resolver = mrc.resolver();
    while(mrc.next(resolver))
    {
        resolver >> c3 >> c2 >> c1;

        unionV.insert(unionV.end(),c1.begin(),c1.end());
        unionV.insert(unionV.end(),c2.begin(),c2.end());
        unionV.insert(unionV.end(),c3.begin(),c3.end());


        cv.push_back(unionV);
        unionV.clear();
    }

    Utils::printCombinations(cv.begin(),cv.end());
    std::cout << "\n" << cv.size() << " combinations!\n\n";
}

void multipleType()
{
    IntVector v1 = {1,2,3};
    DoubleVector v2 = {0.2,0.4};
    StringVector v3 = {"abc","def","ghi","jklm"};

    auto range = addRange(v1.begin(),v1.end(),2)
            .addRange(v2.begin(),v2.end(),1)
            .addRange(v3.begin(),v3.end(),3);

    auto mrc = createCombinator(range);

    IntVector c1(2);
    DoubleVector c2(1);
    StringVector c3(3);

    auto resolver = mrc.resolver();
    int total=0;
    while(mrc.next(resolver))
    {
        resolver >> c3 >> c2 >> c1;

        for(auto it=c1.begin();it!=c1.end();++it) std::cout << *it << ",";
        for(auto it=c2.begin();it!=c2.end();++it) std::cout << *it << ",";
        for(auto it=c3.begin();it!=c3.end();++it) std::cout << *it << ",";

        std::cout << "\n";
        ++total;
    }

    std::cout << "\n" << total << " combinations!\n\n";
}


int main()
{
    singleType();
    multipleType();

    return 0;
}
