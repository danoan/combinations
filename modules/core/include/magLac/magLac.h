#ifndef MAGLAC_MAGLAC_SUGAR_H
#define MAGLAC_MAGLAC_SUGAR_H

#include "magLac/core/base/Range.hpp"
#include "magLac/core/base/Combinator.h"
#include "magLac/core/base/Resolver.h"


namespace magLac {
namespace Private {
using namespace magLac;
using namespace magLac::Core;

template<class TReturn, class TDummy>
TReturn repeat(const TReturn& v, const TDummy& t){
  return v;
}


/*************** initRange ****************/
template<int size, int index, class TNValuesIterator, class TTuple>
auto _initRange(const TNValuesIterator itNValues,
                const TTuple& t){
  auto const &telem = std::get<index>(t);

  if constexpr( size==1){
    return new Range<decltype(telem.begin())>(  telem.begin(),telem.end(), *itNValues);
  }else{
    auto r = _initRange<size-1,index+1>(itNValues + 1, t);
    return r->addRange(telem.begin(),telem.end(), *itNValues);
  }
}

template<class TTuple>
auto initRange(const std::initializer_list<size_t> &NValues,
               const TTuple& t){
    int constexpr tsize = std::tuple_size< TTuple >::value;
    return Private::_initRange<tsize,0>(NValues.begin(),t);
}

/*************** takeFromEach ****************/
template<class TListType, class... TArgs>
class _CombinatorWrapper {
 public:
  typedef std::tuple< std::vector<TListType>, std::vector<TArgs>...> MyData;
  typedef Range< typename std::vector<TListType>::const_iterator, typename std::vector<TArgs>::const_iterator...> MyRange;

  typedef Combinator<MyRange> MyCombinator;
  typedef typename MyCombinator::MyResolver MyResolver;

 public:
  _CombinatorWrapper(const std::initializer_list<size_t> &NValues,
                     const std::initializer_list<TListType> &p_list,
                     const std::initializer_list<TArgs> &... p_args){

    m_data = std::make_tuple( std::vector<TListType>( p_list ),
                              std::vector<TArgs>( p_args )... );

    m_range.reset(  Private::initRange(NValues,m_data) );
    m_combinator.reset( new Combinator(*m_range) );
  }


  _CombinatorWrapper(const _CombinatorWrapper& other)=delete;
  _CombinatorWrapper& operator=(const _CombinatorWrapper& other)=delete;


  template<class TContainer, class... TOthers>
  bool next(TContainer &container, TOthers &... others) {
    MyResolver& resolver = m_combinator->resolver();
    bool hasNext = m_combinator->next(resolver);
    fillUp(resolver, container, others...);

    return hasNext;
  }

  MyCombinator& combinator(){ return *m_combinator; }

 private:
  template<class TResolver, class TContainer, class... TOthers>
  void fillUp(const TResolver &resolver, TContainer &container, TOthers &... others) {
    typedef typename TResolver::PreviousSolver PreviousSolver;

    if constexpr(sizeof...(TOthers) != 0 ) {
      const PreviousSolver& _r = resolver >> container;
      fillUp(_r, others...);
    } else {
      resolver >> container;
    }
  }

 private:
  MyData m_data;
  std::unique_ptr<MyRange> m_range;
  std::unique_ptr<MyCombinator> m_combinator;

};
}

template<class TListType, class... TArgs>
auto takeFromEach(const std::initializer_list<size_t> &NValues,
                  const std::initializer_list<TListType> &p_list,
                  const std::initializer_list<TArgs> &... p_args){
  if (sizeof...(p_args) != NValues.size() - 1)
    throw std::runtime_error("NValues length is different than number of sets");

  return Private::_CombinatorWrapper(NValues,p_list,p_args...);
}

template<size_t N, class TListType, class... TArgs>
auto takeFromEach(const std::initializer_list<TListType> &p_list,
                  const std::initializer_list<TArgs> &... p_args){


  std::initializer_list<size_t> v{ N, Private::repeat(N,p_args)...};
  return Private::_CombinatorWrapper(v,p_list,p_args...);
}

}

#endif //MAGLAC_MAGLAC_SUGAR_H
