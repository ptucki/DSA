#include "Examples.h"

#include <iostream>
#include "BubbleSort.h"
#include "SelectionSort.h"
#include "InsertionSort.h"
#include "Common.h"
#include "Vector.h"

void Example::BubbleSort() {
  auto vec = Util::GetExampleVector();

  Print(vec);

  Alg::Sort::Bubble(vec.begin(), vec.end());

  Print(vec);
}


void Example::SelectionSort() {
  auto vec = Util::GetExampleVector();

  Print(vec);

  Alg::Sort::Selection(vec.begin(), vec.end());

  Print(vec);
}

void Example::InsertionSort() {
  auto vec = Util::GetExampleVector();

  Print(vec);

  Alg::Sort::Insertion(vec.begin(), vec.end());

  Print(vec);
}
