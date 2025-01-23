#ifndef BUBBLE_SORT_H_
#define BUBBLE_SORT_H_

#include <iterator>
#include <algorithm>

namespace Sort {

template<typename InputIt>
void Bubble(InputIt begin, InputIt end) {
  if (std::distance(begin, end) < 2) return;

  for (auto i = begin; i != end;) {
    for (; (i + 1) != end; ++i) {
      if (*i > *(i + 1)) {
        std::iter_swap(i, i+1);
      }
    }
    end = i;
    i = begin;
  }
}

}

#endif // !BUBBLE_SORT_H_
