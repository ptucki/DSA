#ifndef COMMON_PRINT_H_
#define COMMON_PRINT_H_

#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>

template<typename T>
void Print(const std::vector<T>& vec) {
  std::stringstream ss;
  ss << '[';

  std::for_each_n(std::begin(vec), vec.size() -1, [&ss](const auto& item) {
    ss << item << ", ";
  });
  ss << vec.back() << "]\n";

  std::cout << ss.str();
}

#endif // !COMMON_PRINT_H_
