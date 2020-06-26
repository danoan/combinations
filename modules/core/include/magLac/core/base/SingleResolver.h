#ifndef MAGLAC_CORE_BASE_SINGLERESOLVER_H
#define MAGLAC_CORE_BASE_SINGLERESOLVER_H

#include <stdexcept>
#include <vector>

namespace magLac {
namespace Core {
namespace Single {
template<class TIterator>
class Resolver {
 public:
  typedef TIterator Iterator;
  typedef std::vector<size_t> VectorOfHops;

 private:
  TIterator moveIt(TIterator start, size_t hops) {
    for (size_t i = 0; i < hops; ++i) ++start;
    return start;
  }

 public:
  Resolver(TIterator begin,VectorOfHops &hops)
  :m_begin(begin),
  m_hops(hops),
  m_flagIsValid(true){}

  template<class TContainer>
  Resolver &operator>>(TContainer &container) {
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


}
}
}

#endif //MAGLAC_CORE_BASE_SINGLERESOLVER_H
