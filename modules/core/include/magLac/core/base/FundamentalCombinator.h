#ifndef MAGLAC_CORE_BASE_FUNDAMENTALCOMBINATOR_H
#define MAGLAC_CORE_BASE_FUNDAMENTALCOMBINATOR_H

#include <vector>
#include <stack>

#include "Event.h"

namespace magLac {
namespace Core {
class FundamentalCombinator {
 public:
  typedef std::vector<size_t> Container;

 private:
  typedef std::stack<Event> EventStack;

 public:
  FundamentalCombinator(size_t numElements,
                        size_t elemsPerComb) : m_numElements(numElements),
                                             m_elemsPerComb(elemsPerComb) {
    m_currCombination.resize(elemsPerComb);
    m_es.push(Event(Event::END, 0, 0));
    m_es.push(Event(Event::DIVE, 0, 0));
  }

  void restart() {
    m_es.push(Event(Event::END, 0, 0));
    m_es.push(Event(Event::DIVE, 0, 0));
  }

  bool next(Container &container) {
    bool flag = next();
    if (flag) container = m_currCombination;

    return flag;
  }

  bool next() {
    while (!m_es.empty()) {
      Event e = m_es.top();
      m_es.pop();
      switch (e.action) {
        case Event::DIVE: {
          if (e.cIndex >= m_elemsPerComb) {
            m_es.push(Event(Event::DONE, e.cIndex, e.itMove));
          } else {
            if (e.itMove != m_numElements) {
              m_currCombination[e.cIndex] = e.itMove;

              m_es.push(Event(Event::BRANCH, e.cIndex, e.itMove));
              m_es.push(Event(Event::DIVE, e.cIndex + 1, e.itMove + 1));
            }
          }

          break;
        }
        case Event::BRANCH: {
          if ((e.itMove + 1) != m_numElements) {
            m_es.push(Event(Event::DIVE, e.cIndex, e.itMove + 1));
          }

          break;
        }
        case Event::DONE: {
          return true;
        }
        case Event::END: {
          return false;
        }

      }
    }

    return false;
  }

  const Container &get() { return m_currCombination; }

 private:
  size_t m_numElements;
  size_t m_elemsPerComb;

  EventStack m_es;
  Container m_currCombination;
};
}
}
#endif //MAGLAC_CORE_BASE_FUNDAMENTALCOMBINATOR_H
