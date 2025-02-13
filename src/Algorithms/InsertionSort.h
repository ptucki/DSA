#ifndef ALGORITHMS_INSERTION_SORT_H_
#define ALGORITHMS_INSERTION_SORT_H_

#include "Iterator.h"

namespace Alg::Sort {

template<typename InputIt>
void Insertion(InputIt begin, InputIt end) {
  if (Distance(begin, end) < 2) return;

  for (auto it = begin + 1; it != end; ++it) {
    auto current = it;
    auto previous = it -1;
    
    while (*current < *previous) {
      IteratorSwap(current, previous);
      --current;
      if (current == begin) {
        break;
      }
      previous = current - 1;
    }
  }
}

}

#endif // !ALGORITHMS_INSERTION_SORT_H_
