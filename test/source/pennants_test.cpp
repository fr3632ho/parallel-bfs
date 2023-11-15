#include <cassert>
#include <iostream>

#include "bag.hpp"

/**
 * @brief Test insertions to a pennant and merging of pennatns. each time
 * asserting that the size is correct
 *
 * @return int
 */
auto main() -> int
{
  auto pennant_one = pennant_t(), pennant_two = pennant_t();
  // insert 16 elements into p1 and pennant_one
  constexpr int number_of_iterations = 17;
  for (int i = 1; i < number_of_iterations; i++) {
    pennant_one.insert(i);
    pennant_two.insert(i + number_of_iterations - 1);
  }

  std::cout << "p1 size: " << pennant_one.size << std::endl;
  std::cout << "pennant_two size: " << pennant_two.size << std::endl;
  assert(pennant_one.size == 16 && pennant_two.size == 16);

  // merge p1 and pennant_two
  std::cout << "merging pennant_one and pennant_two " << std::endl;
  pennant_t ::merge_tree(&pennant_one, &pennant_two);
  std::cout << "merged pennant_one and pennant_two" << std::endl;
  assert(pennant_one.size == 32);

  return 0;
}