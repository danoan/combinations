[![Build Status](https://travis-ci.com/danoan/magLac.svg?branch=master)](https://travis-ci.com/danoan/magLac)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/759c30de9365427dbaeaaf4bf1668ba5)](https://app.codacy.com/app/danoan/magLac?utm_source=github.com&utm_medium=referral&utm_content=danoan/magLac&utm_campaign=Badge_Grade_Dashboard)
[![codecov](https://codecov.io/gh/danoan/magLac/branch/master/graph/badge.svg)](https://codecov.io/gh/danoan/magLac)



<img src="logo.png" width="320px">

magLac (Multiple type Lazy Combinations) makes combinations 
simpler! magLac is a generic type library and multithread ready.

# Single set combination
```c++
    #include <magLac/magLac.h>
    
    using namespace magLac;
    
    vector<int> out(2);
    auto explorer = takeFromEach<2>( {1,2,3} );
    while(explorer.next(out) ){ 
        for_each(out.begin(),out.end(),[](int x){ cout << x << ","; } );
        cout << "\n"; 
    }
    
    //Outputs
    1,2
    1,3
    2,3    
```

# Multiple set combination
```c++
    #include <magLac/magLac.h>
    
    using namespace magLac;
    
    vector<int> outInt(2);
    vector<string> outStr(3);
    auto explorer = takeFromEach( {2,3}, {1,2,3}, {"Sun","Lake","Water","Summer"} );
    while(explorer.next(outInt,outStr) ){ 
        for_each(outInt.begin(),outInt.end(),[](int x){ cout << x << ","; } );
        for_each(outStr.begin(),outStr.end(),[](string x){ cout << x << ","; } );
        cout << "\n"; 
    }
    
    //Outputs
    1,2,"Sun","Lake","Water"
    1,2,"Sun","Lake","Summer"
    1,2,"Sun","Water","Summer"
    1,2,"Lake","Water","Summer"
    1,3,"Sun","Lake","Water"
    1,3,"Sun","Lake","Summer"
    1,3,"Sun","Water","Summer"
    1,3,"Lake","Water","Summer"    
    2,3,"Sun","Lake","Water"
    2,3,"Sun","Lake","Summer"
    2,3,"Sun","Water","Summer"
    2,3,"Lake","Water","Summer" 
```

# Multithread execution

```c++
    #include <magLac/magLac.h>
    #include <magLac/multithread.h>
    
    using namespace magLac;
    using namespace magLac::Core;
    
    int sizeCombination=5;
    int m_numThreads = 4;
    int m_queriesPerThread = 1000;
    
    vector< int > v = veryLongVector();
    auto m_range = addRange(v.begin(),v.end(),sizeCombination);
    auto combinator = Combinator(m_range);
    
    MyThreadData data;
    auto planner = slice(combinator, data, m_numThreads, m_queriesPerThread);
    typedef decltype(planner)::MyThreadInfo MyThreadInfo;

    planner.run( [&sizeCombinations](MyThreadInfo&& ti) mutable
                   {
                       vector<int> out(sizeCombinations) out;
                       ti.resolver >> out;

                       for_each(out.begin(),out.end(),[](int x){ cout << x << ","; } );
                       cout << "\n";
                   });
    
``` 

# More examples

Take a look in the lab/example folder

# Install
```
cd [magLac Source]
mkdir build
cd build 
cmake .. [-DCMAKE_INSTALL_PREFIX={INSTALLATION DIRECTORY}] 
[-DBUILD_TESTS={ON,OFF} ] 
[-DBUILD_EXAMPLES={ON,OFF} ]  
[-DBUILD_BENCHMARK={ON,OFF} ] 
make install
```