#ifndef MAGLAC_MAGLAC_SUGAR_H
#define MAGLAC_MAGLAC_SUGAR_H

#include "magLac/core/base/Range.hpp"
#include "magLac/core/base/Combinator.h"
#include "magLac/core/base/Resolver.h"

namespace magLac {
namespace Private {
using namespace magLac;
using namespace magLac::Core;

/*************** initRange ****************/
template<class TListType, class... TArgs>
auto _initRange(unsigned int N,
                const std::initializer_list<TListType> &p_list,
                const std::initializer_list<TArgs> &... p_args){
  typedef Range<decltype(p_list.begin()), decltype(p_args.begin())...> OutputType;
  if constexpr (sizeof...(TArgs) == 0) {
    return OutputType(p_list.begin(), p_list.end(), N);
  } else {
    auto r = _initRange(N, p_args...);
    return r.addRange(p_list.begin(), p_list.end(), N);
  }
}

template<class TNValuesIterator, class TListType, class... TArgs>
auto _initRange(const TNValuesIterator itNValues,
                const std::initializer_list<TListType> &p_list,
                const std::initializer_list<TArgs> &... p_args){
  typedef Range<decltype(p_list.begin()), decltype(p_args.begin())...> OutputType;
  if constexpr (sizeof...(TArgs) == 0) {
    return OutputType(p_list.begin(), p_list.end(), *itNValues);
  } else {
    auto r = _initRange(itNValues + 1, p_args...);
    return r.addRange(p_list.begin(), p_list.end(), *itNValues);
  }
}

/*************** takeFromEach ****************/
template<class TRange>
class _CombinatorWrapper {
 public:
  typedef TRange MyRange;
  typedef Combinator<MyRange> MyCombinator;
  typedef typename MyCombinator::MyResolver MyResolver;

 public:
  _CombinatorWrapper(MyRange &range)
      : range(range),
        combinator(this->range) {}

  template<class TContainer, class... TArgs>
  bool next(TContainer &container, TArgs &... args) {
    MyResolver resolver = combinator.resolver();
    bool hasNext = combinator.next(resolver);
    fillUp(resolver, container, args...);

    return hasNext;
  }

 private:
  template<class TResolver, class TContainer, class... TArgs>
  void fillUp(TResolver &resolver, TContainer &container, TArgs &... args) {
    if constexpr(sizeof...(TArgs) != 0) {
      auto _r = resolver >> container;
      fillUp(_r, args...);
    } else {
      resolver >> container;
    }

  }

 public:
  MyRange range;
  MyCombinator combinator;

};
}

template<unsigned int N, class TListType, class... TArgs>
auto initRange(const std::initializer_list<TListType> &p_list,
               const std::initializer_list<TArgs> &... p_args){
  return Private::_initRange(N, p_list, p_args...);
}

template<unsigned int N, class TListType, class... TArgs>
auto takeFromEach(const std::initializer_list<TListType> &p_list,
                  const std::initializer_list<TArgs> &... p_args) {
  auto range = Private::initRange<N>(p_list, p_args...);
  return Private::_CombinatorWrapper(range);
}

template<class TListType, class... TArgs>
auto initRange(const std::initializer_list<size_t> &NValues,
               const std::initializer_list<TListType> &p_list,
               const std::initializer_list<TArgs> &... p_args){
  if (sizeof...(p_args) != NValues.size() - 1)
    throw std::runtime_error("NValues length is different than number of sets");
  else return Private::_initRange(NValues.begin(), p_list, p_args...);
}

template<class TListType, class... TArgs>
auto takeFromEach(const std::initializer_list<size_t> &NValues,
                  const std::initializer_list<TListType> &p_list,
                  const std::initializer_list<TArgs> &... p_args){
  auto range = Private::initRange(NValues, p_list, p_args...);
  return Private::_CombinatorWrapper(range);
}

}

#endif //MAGLAC_MAGLAC_SUGAR_H
