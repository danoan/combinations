#ifndef MAGLAC_CORE_BASE_RESOLVER_H
#define MAGLAC_CORE_BASE_RESOLVER_H

#include <stdexcept>

namespace magLac {
namespace Core {

template<class TIterator>
class BaseResolver {
 public:
  typedef TIterator Iterator;
  typedef std::vector<size_t> VectorOfHops;

 private:
  TIterator moveIt(TIterator start, size_t hops) {
    for (size_t i = 0; i < hops; ++i) ++start;
    return start;
  }

 public:
  BaseResolver(TIterator begin,VectorOfHops &hops)
      :m_begin(begin),
       m_hops(hops),
       m_flagIsValid(true){}

  template<class TContainer>
  BaseResolver &operator>>(TContainer &container) {
    if (!m_flagIsValid) throw std::runtime_error("Resolver is exhausted!");

    size_t pos = 0;
    for (auto it = m_hops.begin(); it != m_hops.end(); ++it, ++pos) {
      container[pos] = *moveIt(m_begin, *it);
    }
    m_flagIsValid = false;

    return *this;
  }

 private:
  TIterator m_begin;
  VectorOfHops m_hops;

  bool m_flagIsValid;
};

template<class TRange, bool= TRange::isFirst>
class Resolver {
};

template<class TRange>
class Resolver<TRange, true> {
 public:
  typedef std::vector<size_t> VectorOfHops;
  typedef Resolver<TRange, true> Self;

 public:
  Resolver(TRange &range) : range(range), previousSolver(*this) {};

  void set(const VectorOfHops &hops) { this->hops = hops; }

  template<typename TContainer>
  void operator>>(TContainer &container) {
    auto sr = BaseResolver(range.begin(), hops);
    sr >> container;
  }

 public:
  TRange range;
  VectorOfHops hops;

  Self &previousSolver;
};

template<class TRange>
class Resolver<TRange, false> {
 public:
  typedef std::vector<size_t> VectorOfHops;

  typedef typename TRange::PreviousRange PreviousRange;
  typedef Resolver<PreviousRange, PreviousRange::isFirst> PreviousSolver;

 public:
  Resolver(TRange &range) : range(range),
                            previousSolver(PreviousSolver(range.previous)) {}

  void set(const VectorOfHops &hops) { this->hops = hops; }

  template<typename TContainer>
  PreviousSolver &operator>>(TContainer &container) {
    auto sr = BaseResolver(range.begin(), hops);
    sr >> container;

    return previousSolver;
  }

 public:
  TRange range;
  VectorOfHops hops;

  PreviousSolver previousSolver;
};

}
}
#endif //MAGLAC_CORE_BASE_RESOLVER_H
