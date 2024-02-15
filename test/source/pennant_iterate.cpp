#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#include "bag.hpp"
constexpr int iterations = 32;

void test_iterate_full()
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
}

void test_iterate_empty()
{
  auto pennant_one = pennant_t();
  std::vector<int> vec;
  for (auto n : pennant_one) {
    std::cout << n << std::endl;
    vec.emplace_back(n);
  }
  assert(vec.size() == 0);
}

void test_iterate_single()
{
  auto pennant_one = pennant_t();
  pennant_one.insert(0);
  std::vector<int> vec;
  for (auto n : pennant_one) {
    std::cout << n << std::endl;
    vec.emplace_back(n);
  }
  assert(pennant_one.size == 1);
  assert(vec.size() == 1);
}

void test_iterate_two()
{
  auto pennant_one = pennant_t();
  pennant_one.insert(0);
  pennant_one.insert(1);
  std::vector<int> vec;
  for (auto n : pennant_one) {
    std::cout << n << std::endl;
    vec.emplace_back(n);
  }
  assert(pennant_one.size == 2);
  assert(vec.size() == 2);
}

/**
 * @brief Test insertions to a pennant and merging of pennatns. each time
 * asserting that the size is correct
 *
 * @return int
 */
auto main() -> int
{
  test_iterate_full();
  test_iterate_empty();
  test_iterate_single();
  test_iterate_two();
  return 0;
}