#include "magLac/lab/logger/logger.h"

#include "magLac/lab/test/core/base/fundamental-combinator/correcteness.h"
#include "magLac/lab/test/core/base/fundamental-combinator/execution.h"

#include "magLac/lab/test/core/multiple/combinator/correcteness.h"
#include "magLac/lab/test/core/multiple/resolver/correcteness.h"

#include "magLac/lab/test/core/single/combinator/correcteness.h"

#include "magLac/lab/test/core/multithread/correcteness.h"
#include "magLac/lab/test/core/multithread/execution.h"

#include "magLac/lab/test/core/base/range/correcteness.h"

using namespace magLac::Test;

int main(int argc, char *argv[]) {
  magLac::Logger logger(std::cout, false);

  FundamentalCombinator::correcteness(logger);
  FundamentalCombinator::execution(logger);

  MultipleResolver::correcteness(logger);
  MultipleCombinator::correcteness(logger);

  SingleCombinator::correcteness(logger);

  Multithread::correcteness(logger);
  Multithread::execution(logger);

  Range::correcteness(logger);

  return 0;
}