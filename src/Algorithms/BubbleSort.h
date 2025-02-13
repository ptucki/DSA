#ifndef ALGORITHMS_BUBBLE_SORT_H_
#define ALGORITHMS_BUBBLE_SORT_H_

#include "Iterator.h"

namespace Alg::Sort {

template<typename InputIt>
void Bubble(InputIt begin, InputIt end) {
  if (Distance(begin, end) < 2) return;

  for (auto i = begin; i != end;) {
    for (; (i + 1) != end; ++i) {
      if (*i > *(i + 1)) {
        IteratorSwap(i, (i + 1));
      }
    }
    end = i;
    i = begin;
  }
}

}

#endif // !ALGORITHMS_BUBBLE_SORT_H_
