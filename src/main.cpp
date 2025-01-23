#include <vector>
#include "BubbleSort.h"
#include "Common.h"

int main(int argc, char* argv[]) {

  std::vector<int> a = {7,9,2,5,3,4,1,8};

  Print(a);

  Sort::Bubble(a.begin() + 2, a.begin() + 7);

  Print(a);
  return 0;
}
