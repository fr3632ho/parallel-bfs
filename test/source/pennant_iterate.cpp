#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#include "bag.hpp"
constexpr int iterations = 32;

/**
 * @brief Test insertions to a pennant and merging of pennatns. each time
 * asserting that the size is correct
 *
 * @return int
 */
auto main() -> int
{
  auto pennant_one = pennant_t();

  for (int i = 0; i < iterations; i++) {
    pennant_one.insert(i);
  }
  pennant_one.display_inorder();
  std::vector<int> vec;
  const char* dlm = "";
  for (auto& n : pennant_one) {
    std::cout << dlm << n;
    vec.emplace_back(n);
    dlm = " ";
  }

  std::cout << std::endl;
  sort(vec.begin(), vec.end());
  assert(vec.size() == iterations);
  for (int i = 0; i < iterations; i++) {
    assert(vec[i] == i);
  }

  std::cout << "TEST PASSED" << std::endl;
  return 0;
}