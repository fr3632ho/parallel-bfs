#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#include "bag.hpp"

auto print_vec(std::vector<int> vec) -> void
{
  const char* dlm = "";
  for (int i = 0; i < vec.size(); i++) {
    std::cout << dlm << vec[i];
    dlm = " ";
  }
  std::cout << std::endl;
}

auto test_disjoin_pennants(pennant_t* pennant_one, pennant_t* pennant_two)
    -> bool
{
  std::vector<int> element_one, element_two;
  pennant_t::get_elements(pennant_one, &element_one);
  pennant_t::get_elements(pennant_two, &element_two);
  assert(element_one.size() == element_two.size());
  sort(element_one.begin(), element_one.end());
  sort(element_two.begin(), element_two.end());
  print_vec(element_one), print_vec(element_two);
  for (int i = 0; i < element_one.size(); i++) {
    assert(element_one[i] != element_two[i]);
  }
  return true;
}

/**
 * @brief Test insertions to a pennant and merging of pennatns. each time
 * asserting that the size is correct
 *
 * @return int
 */
auto main() -> int
{
  auto *pennant_one = new pennant_t(), *pennant_two = new pennant_t();

  for (int i = 0; i < 64; i++) {
    pennant_one->insert(i);
  }

  std::cout << "pennant_one size: " << pennant_one->size << std::endl;
  assert(pennant_one->size == 64);
  pennant_t ::split_pennant(pennant_one, pennant_two);
  std::cout << "pennant_one size: " << pennant_one->size << std::endl;
  std::cout << "pennant_two size: " << pennant_two->size << std::endl;
  assert(pennant_one->size == 32 && pennant_two->size == 32);

  std::cout << "PENNANT_ONE" << std::endl;
  pennant_one->display_inorder();
  std::cout << "PENNANT_TWO" << std::endl;
  pennant_two->display_inorder();

  test_disjoin_pennants(pennant_one, pennant_two);
  delete pennant_two;
  pennant_two = new pennant_t();

  pennant_t ::split_pennant(pennant_one, pennant_two);
  std::cout << "pennant_one size: " << pennant_one->size << std::endl;
  std::cout << "pennant_two size: " << pennant_two->size << std::endl;
  assert(pennant_one->size == 16 && pennant_two->size == 16);

  test_disjoin_pennants(pennant_one, pennant_two);
  delete pennant_two;
  pennant_two = new pennant_t();
  pennant_t ::split_pennant(pennant_one, pennant_two);
  std::cout << "pennant_one size: " << pennant_one->size << std::endl;
  std::cout << "pennant_two size: " << pennant_two->size << std::endl;
  assert(pennant_one->size == 8 && pennant_two->size == 8);

  test_disjoin_pennants(pennant_one, pennant_two);
  delete pennant_two;
  pennant_two = new pennant_t();
  pennant_t ::split_pennant(pennant_one, pennant_two);
  std::cout << "pennant_one size: " << pennant_one->size << std::endl;
  std::cout << "pennant_two size: " << pennant_two->size << std::endl;
  assert(pennant_one->size == 4 && pennant_two->size == 4);

  test_disjoin_pennants(pennant_one, pennant_two);
  delete pennant_two;
  pennant_two = new pennant_t();
  pennant_t ::split_pennant(pennant_one, pennant_two);
  std::cout << "pennant_one size: " << pennant_one->size << std::endl;
  std::cout << "pennant_two size: " << pennant_two->size << std::endl;
  assert(pennant_one->size == 2 && pennant_two->size == 2);

  test_disjoin_pennants(pennant_one, pennant_two);
  delete pennant_two;
  pennant_two = new pennant_t();
  pennant_t ::split_pennant(pennant_one, pennant_two);
  std::cout << "pennant_one size: " << pennant_one->size << std::endl;
  std::cout << "pennant_two size: " << pennant_two->size << std::endl;
  assert(pennant_one->size == 1 && pennant_two->size == 1);

  test_disjoin_pennants(pennant_one, pennant_two);
  delete pennant_two;
  pennant_two = new pennant_t();
  pennant_t ::split_pennant(pennant_one, pennant_two);
  std::cout << "pennant_one size: " << pennant_one->size << std::endl;
  std::cout << "pennant_two size: " << pennant_two->size << std::endl;
  assert(pennant_one->size == 1 && pennant_two->size == 0);
  return 0;
}