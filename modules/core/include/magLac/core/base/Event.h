#ifndef MAGLAC_CORE_BASE_EVENT_H
#define MAGLAC_CORE_BASE_EVENT_H

namespace magLac {
namespace Core {
struct Event {
  enum Action { DIVE, BRANCH, DONE, END };
  Event(Action action, size_t cIndex, size_t itMove) : action(action), cIndex(cIndex), itMove(itMove) {}

  Action action;
  size_t cIndex;
  size_t itMove;
};
}
}

#endif  //MAGLAC_CORE_BASE_EVENT_H
