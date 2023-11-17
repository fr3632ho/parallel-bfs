#include <cassert>
#include <iostream>

#include "bag.hpp"

auto main() -> int
{
  bag_t bag_1(100), bag_2(100);
  for (int i = 0; i < 3; i++) {
    insert(&bag_1, i);
  }
  for (int i = 0; i < 6; i++) {
    insert(&bag_2, i);
  }
  std::cout << "Bag 1 size: " << bag_1.num_elements() << std::endl;
  std::cout << "Bag 2 size: " << bag_2.num_elements() << std::endl;
  assert(bag_1.num_elements() == 3);
  assert(bag_2.num_elements() == 6);
  std::cout << "BEFORE:" << std::endl;
  display_bag_in_binary(&bag_1);
  display_bag_in_binary(&bag_2);

  merge(&bag_1, &bag_2);
  std::cout << "AFTER:" << std::endl;
  std::cout << "Bag 1 size: " << bag_1.num_elements() << std::endl;
  std::cout << "Bag 2 size: " << bag_2.num_elements() << std::endl;
  std::cout << "Bag 1 = ";
  display_bag_in_binary(&bag_1);
  std::cout << "Bag 2 = ";
  display_bag_in_binary(&bag_2);
  assert(bag_1.num_elements() == 9);

  return 0;
}
