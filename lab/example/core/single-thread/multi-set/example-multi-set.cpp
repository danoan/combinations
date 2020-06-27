#include <iostream>
#include <string>
#include <vector>
#include <functional>

#include "magLac/magLac.h"

using namespace magLac;
using namespace std;

typedef vector<int> IntVector;
typedef vector<double> DoubleVector;
typedef vector<std::string> StringVector;

void singleType() {
  size_t constexpr N = 2;
  IntVector c1(N), c2(N), c3(N);

  auto combExplorer = takeFromEach<N>({1, 2, 3}, {4, 5, 6}, {7, 8, 9, 10});
  size_t count = 0;
  while (combExplorer.next(c1, c2, c3)) {
    for_each(c1.begin(), c1.end(), [](auto x) { cout << x << ","; });
    for_each(c2.begin(), c2.end(), [](auto x) { cout << x << ","; });
    for_each(c3.begin(), c3.end(), [](auto x) { cout << x << ","; });

    cout << "\n";
    count++;
  }

  cout << "\n" << count << " combinations!\n" << endl;
}

void multipleType() {

  vector<int> outInt(2);
  vector<string> outStr(3);

  auto explorer = takeFromEach( {2,3}, {1,2,3}, {"Sun","Lake","Water","Summer"} );
  size_t count = 0;
  while(explorer.next(outInt,outStr) ){
    for_each(outInt.begin(),outInt.end(),[](int x){ cout << x << ","; } );
    for_each(outStr.begin(),outStr.end(),[](string x){ cout << x << ","; } );
    cout << "\n";
    count++;
  }

  cout << "\n" << count << " combinations!\n" << endl;
}

void differentTakeValues() {
  using namespace magLac::Core;

  IntVector c1(2);
  DoubleVector c2(1);
  StringVector c3(3);

  auto combExplorer = takeFromEach({2, 1, 3}, {1, 2, 3}, {0.2, 0.4}, {"Sun","Lake","Water","Summer"});
  size_t count = 0;
  while (combExplorer.next(c1, c2, c3)) {

    for_each(c1.begin(), c1.end(), [](auto x) { cout << x << ","; });
    for_each(c2.begin(), c2.end(), [](auto x) { cout << x << ","; });
    for_each(c3.begin(), c3.end(), [](auto x) { cout << x << ","; });

    cout << "\n";
    ++count;
  }

  cout << "\n" << count << " combinations!\n" << endl;
}

int main() {
  cout << "********Single Type********" << endl;
  singleType();

  cout << "********Multiple Type********" << endl;
  multipleType();

  cout << "********Different take values********" << endl;
  differentTakeValues();

  return 0;
}