[![Build Status](https://travis-ci.com/danoan/magLac.svg?branch=master)](https://travis-ci.com/danoan/magLac)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/759c30de9365427dbaeaaf4bf1668ba5)](https://app.codacy.com/app/danoan/magLac?utm_source=github.com&utm_medium=referral&utm_content=danoan/magLac&utm_campaign=Badge_Grade_Dashboard)

<img src="logo.png" width="320px">

MagLac (Multiple type Lazy Combinations) allows to iterate over
combinations of many lists of different types in a lazy fashion. 

# Example of use

```c++
    #include <iostream>
    #include <string>
    
    #include "magLac/core/base/Range.hpp"
    #include "magLac/core/multiple/Combinator.h"
    #include "magLac/utils/displayUtils.h"
    
    using namespace magLac;
    using namespace magLac::Core;
    
    int main(int argc, char* argv[])
    {
        std::vector<int> v1 = {1,2,3};
        std::vector<double> v2 = {0.2,0.4};
        std::vector<string> v3 = {"abc","def","ghi","jklm"};
    
        auto range = addRange(v1.begin(),v1.end(),2)
                    .addRange(v2.begin(),v2.end(),1)
                    .addRange(v3.begin(),v3.end(),3);
    
        auto mrc = Multiple::createCombinator(range);
    
        std::vector<int> c1(2);
        std::vector<double> c2(1);
        std::vector<string> c3(3);
    
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
        
        return 0;
    }        
    
    //Outputs
    1,2,0.2,abc,def,ghi,
    1,3,0.2,abc,def,ghi,
    2,3,0.2,abc,def,ghi,
    1,2,0.4,abc,def,ghi,
    1,3,0.4,abc,def,ghi,
    2,3,0.4,abc,def,ghi,
    1,2,0.2,abc,def,jklm,
    1,3,0.2,abc,def,jklm,
    2,3,0.2,abc,def,jklm,
    1,2,0.4,abc,def,jklm,
    1,3,0.4,abc,def,jklm,
    2,3,0.4,abc,def,jklm,
    1,2,0.2,abc,ghi,jklm,
    1,3,0.2,abc,ghi,jklm,
    2,3,0.2,abc,ghi,jklm,
    1,2,0.4,abc,ghi,jklm,
    1,3,0.4,abc,ghi,jklm,
    2,3,0.4,abc,ghi,jklm,
    1,2,0.2,def,ghi,jklm,
    1,3,0.2,def,ghi,jklm,
    2,3,0.2,def,ghi,jklm,
    1,2,0.4,def,ghi,jklm,
    1,3,0.4,def,ghi,jklm,
    2,3,0.4,def,ghi,jklm,
    
    24 combinations!
``` 
