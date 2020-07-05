#ifndef MAGLAC_LAB_BENCHMARK_TECHNIQUES_EAGERRECURSIVE_H
#define MAGLAC_LAB_BENCHMARK_TECHNIQUES_EAGERRECURSIVE_H

#include <vector>

namespace magLac {
namespace EagerRecursive {
template<class T>
using CombinationsVector = std::vector<std::vector<T> >;

template<class TElementType>
using CombinationsIterator = typename CombinationsVector<TElementType>::const_iterator;

enum Status { FAILURE, SUCCESS, CONTINUE };

/***
 * Computes all integer combinations of size k starting with *begin
 * @param combs
 * @param curr
 * @param k
 * @param begin
 * @param end
 * @return
 */
template<class TElementType, class TElementIterator>
Status rec_combinations(CombinationsVector<TElementType> &combs,
                        std::vector<TElementType> &curr,
                        size_t k,
                        TElementIterator begin,
                        TElementIterator end);

/***
 * Computes all combinations of size k for a list of integers
 * @param k
 * @param begin
 * @param end
 * @return
 */
template<class TElementType, class TElementIterator>
CombinationsVector<TElementType> combinations(size_t k,
                                              TElementIterator begin,
                                              TElementIterator end);

}
}

#include "eager-recursive.hpp"

#endif //MAGLAC_LAB_BENCHMARK_TECHNIQUES_EAGERRECURSIVE_H
