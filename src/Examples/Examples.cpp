#include "Examples.h"

#include <iostream>
#include "BubbleSort.h"
#include "Common.h"
#include "Vector.h"

void Example::BubbleSort() {
  Ds::Vector<int> vec;

  vec.PushBack(24);
  vec.PushBack(23);
  vec.PushBack(41);
  vec.PushBack(21);
  vec.PushBack(12);

  Print(vec);

  Alg::Sort::Bubble(vec.begin(), vec.end());

  Print(vec);
}
