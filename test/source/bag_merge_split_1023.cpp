#include <cassert>
#include <iostream>

#include "bag.hpp"

auto main() -> int
{
  bag_t bag_1(4096), bag_2(4096);
  for (int i = 0; i < 1023; i++) {
    insert(&bag_1, i);
  }
  split(&bag_1, &bag_2);
  std::cout << "Bag 1 size: " << bag_1.num_elements() << std::endl;
  std::cout << "Bag 2 size: " << bag_2.num_elements() << std::endl;
  assert(bag_1.num_elements() == 512);
  assert(bag_2.num_elements() == 511);
  merge(&bag_1, &bag_2);
  std::cout << "Bag 1 size: " << bag_1.num_elements() << std::endl;
  std::cout << "Bag 2 size: " << bag_2.num_elements() << std::endl;
  assert(bag_1.num_elements() == 1023);
  assert(bag_2.num_elements() == 0);
  split(&bag_1, &bag_2);
  std::cout << "Bag 1 size: " << bag_1.num_elements() << std::endl;
  std::cout << "Bag 2 size: " << bag_2.num_elements() << std::endl;
  assert(bag_1.num_elements() == 512);
  assert(bag_2.num_elements() == 511);
  merge(&bag_2, &bag_1);
  std::cout << "Bag 1 size: " << bag_1.num_elements() << std::endl;
  std::cout << "Bag 2 size: " << bag_2.num_elements() << std::endl;
  assert(bag_1.num_elements() == 0);
  assert(bag_2.num_elements() == 1023);
  return 0;
}