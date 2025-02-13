#ifndef ALGORITHMS_SELECTION_SORT_H_
#define ALGORITHMS_SELECTION_SORT_H_

#include "Iterator.h"

namespace Alg::Sort {

template<typename InputIt>
void Selection(InputIt begin, InputIt end) {
  if (Distance(begin, end) < 2) return;

  for (auto i = begin; i != end;) {
    auto pos = i;
    auto min = i;

    for (;i != end; i++) {
      if (*i < *min) {
        min = i;
      }
    }
    
    IteratorSwap(pos, min);
    i = pos + 1;
  }
}

}

#endif // !ALGORITHMS_SELECTION_SORT_H_
