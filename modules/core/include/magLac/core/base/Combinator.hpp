#include "Combinator.h"

template<class TRange>
template<class TResolver>
void Combinator<TRange>::setResolver(TResolver &resolver) {
  setResolver(resolver, 0);
}

template<class TRange>
template<class TResolver>
void Combinator<TRange>::setResolver(TResolver &resolver, size_t proxyVectorIndex) {

  if (proxyVectorIndex < m_numRanges) {
    resolver.set(m_fv[proxyVectorIndex].get());
    setResolver(resolver.previousSolver, proxyVectorIndex + 1);
  }

}

template<class TRange>
typename Combinator<TRange>::MyResolver Combinator<TRange>::resolver() {
  return MyResolver(m_range);
}

template<class TRange>
Combinator<TRange>::Combinator(MyRange &range):
    m_range(range),
    m_numRanges(0) {
  m_es.push(Event(Event::END, 0, 0));
  m_es.push(Event(Event::DIVE, 0, 0));

  initializeFundamentalVector(m_fv, range);
  m_numRanges = m_fv.size();
}

template<class TRange>
bool Combinator<TRange>::next(MyResolver &resolver) {
  while (!m_es.empty()) {
    Event e = m_es.top();
    m_es.pop();

    switch (e.action) {
      case Event::DIVE: {
        if (e.cIndex >= this->m_numRanges) {
          m_es.push(Event(Event::DONE, e.cIndex, 0));
        } else {
          FundamentalCombinator &fc = m_fv[e.cIndex];

          if (fc.next()) {
            m_es.push(Event(Event::BRANCH, e.cIndex, 0));
            m_es.push(Event(Event::DIVE, e.cIndex + 1, 0));
          } else {
            fc.restart();
          }

        }

        break;
      }
      case Event::BRANCH: {
        m_es.push(Event(Event::DIVE, e.cIndex, 0));
        break;
      }
      case Event::DONE: {
        setResolver(resolver);
        return true;
      }
      case Event::END: {
        return false;
      }

    }
  }

  return false;
}
