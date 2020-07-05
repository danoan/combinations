#ifndef MAGLAC_LAB_BENCHMARK_TECHNIQUES_LAZYNONRECURSIVE_EVENT_H
#define MAGLAC_LAB_BENCHMARK_TECHNIQUES_LAZYNONRECURSIVE_EVENT_H

namespace magLac {
namespace LazyNonRecursive {
struct Event {
  enum Action { DIVE, BRANCH, DONE, END };
  Event(Action action, size_t cIndex, size_t itMove) : action(action), cIndex(cIndex), itMove(itMove) {}

  Action action;
  size_t cIndex;
  size_t itMove;
};
}
}

#endif //MAGLAC_LAB_BENCHMARK_TECHNIQUES_LAZYNONRECURSIVE_EVENT_H
