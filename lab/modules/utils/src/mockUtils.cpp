#include "magLac/lab/utils/mockUtils.h"

namespace magLac {
namespace Utils {
IntVector createIntegerVector(int nelems) {
  std::vector<int> intVector;
  int x = 1;
  while (nelems > 0) {
    intVector.push_back(x++);
    --nelems;
  }

  return intVector;
}
}
}