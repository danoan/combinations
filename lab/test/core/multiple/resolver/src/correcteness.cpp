#include "magLac/lab/test/core/multiple/resolver/correcteness.h"

using namespace magLac::Core;

namespace magLac {
namespace Test {
namespace MultipleResolver {
bool correcteness(Logger &logger) {
  logger << Logger::HeaderTwo << "Test Correcteness" << Logger::Normal;

  IntVector v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  auto b1 = v.begin();
  auto e1 = v.begin() + 3;

  auto b2 = v.begin() + 3;
  auto e2 = v.begin() + 6;

  auto b3 = v.begin() + 6;
  auto e3 = v.end();

  auto range = addRange(b1, e1, 2).addRange(b2, e2, 2).addRange(b3, e3, 2);
  auto mr = Resolver<decltype(range),false>(range);

  std::vector<size_t> hops1 = {0, 1};
  std::vector<size_t> hops2 = {0, 2};
  std::vector<size_t> hops3 = {1, 2};

  mr.set(hops1);
  auto &previous = mr.previousSolver;
  previous.set(hops2);
  auto &previous2 = previous.previousSolver;
  previous2.set(hops3);

  IntVector c1(2);
  IntVector c2(2);
  IntVector c3(2);

  mr >> c1 >> c2 >> c3;

  bool flag = true;
  flag = flag && check(c1.begin(), c1.end(), {7, 8});
  flag = flag && check(c2.begin(), c2.end(), {4, 6});
  flag = flag && check(c3.begin(), c3.end(), {2, 3});

  logger << "Passed: " << flag;

  return flag;
}
}
}
}