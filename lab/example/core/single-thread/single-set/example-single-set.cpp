#include <iostream>
#include <vector>
#include <functional>

#include "magLac/magLac.h"

using namespace magLac;
using namespace std;

typedef vector<int> IntVector;

int main(int argc, char *argv[]) {
  unsigned long int constexpr N = 3;
  auto combExplorer = takeFromEach<N>({1, 2, 3, 4, 5});

  vector<int> nextComb(N);
  int count = 0;
  while (combExplorer.next(nextComb)) {
    for_each(nextComb.begin(), nextComb.end(), [](auto x) { cout << x << ","; });
    cout << "\n";
    count++;
  }
  cout << "\n" << count << " combinations!\n" << endl;

  return 0;
}
