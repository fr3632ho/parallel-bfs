#include <cassert>
#include <iostream>

#include "bag.hpp"

auto main() -> int
{
  bag_t bag_1(4096), bag_2(4096);
  for (int i = 0; i < 1023; i++) {
    bag_1.insert(i);
  }
  bag_1.split(&bag_2);
  std::cout << "Bag 1 size: " << bag_1.num_elements() << std::endl;
  std::cout << "Bag 2 size: " << bag_2.num_elements() << std::endl;
  assert(bag_1.num_elements() == 512);
  assert(bag_2.num_elements() == 511);
  bag_1.merge(&bag_2);
  std::cout << "Bag 1 size: " << bag_1.num_elements() << std::endl;
  std::cout << "Bag 2 size: " << bag_2.num_elements() << std::endl;
  assert(bag_1.num_elements() == 1023);
  assert(bag_2.num_elements() == 0);
  bag_1.split(&bag_2);
  std::cout << "Bag 1 size: " << bag_1.num_elements() << std::endl;
  std::cout << "Bag 2 size: " << bag_2.num_elements() << std::endl;
  assert(bag_1.num_elements() == 512);
  assert(bag_2.num_elements() == 511);
  bag_2.merge(&bag_1);
  std::cout << "Bag 1 size: " << bag_1.num_elements() << std::endl;
  std::cout << "Bag 2 size: " << bag_2.num_elements() << std::endl;
  assert(bag_1.num_elements() == 0);
  assert(bag_2.num_elements() == 1023);
  return 0;
}