#ifndef MAGLAC_LAB_BENCHMARK_TECHNIQUES_LAZYNONRECURSIVE_EVENT_H
#define MAGLAC_LAB_BENCHMARK_TECHNIQUES_LAZYNONRECURSIVE_EVENT_H

namespace magLac {
namespace LazyNonRecursive {
struct Event {
  typedef unsigned long int Size;
  enum Action { DIVE, BRANCH, DONE, END };
  Event(Action action, Size cIndex, Size itMove) : action(action), cIndex(cIndex), itMove(itMove) {}

  Action action;
  Size cIndex;
  Size itMove;
};
}
}

#endif //MAGLAC_LAB_BENCHMARK_TECHNIQUES_LAZYNONRECURSIVE_EVENT_H
