#include <cassert>
#include <iostream>

#include "bag.hpp"

auto main() -> int
{
  bag_t bag_1(4096), bag_2(4096);
  for (int i = 0; i < 1023; i++) {
    bag_1.insert(i);
  }
  for (int i = 0; i < 1023; i++) {
    bag_2.insert(i);
  }
  std::cout << "Bag 1 size: " << bag_1.num_elements() << std::endl;
  std::cout << "Bag 2 size: " << bag_2.num_elements() << std::endl;
  assert(bag_1.num_elements() == 1023);
  assert(bag_2.num_elements() == 1023);
  std::cout << "BEFORE:" << std::endl;
  bag_1.display_bag_in_binary();
  bag_2.display_bag_in_binary();

  bag_1.merge(&bag_2);
  std::cout << "AFTER:" << std::endl;
  std::cout << "Bag 1 size: " << bag_1.num_elements() << std::endl;
  std::cout << "Bag 2 size: " << bag_2.num_elements() << std::endl;
  std::cout << "Bag 1 = ";
  bag_1.display_bag_in_binary();
  std::cout << "Bag 2 = ";
  bag_2.display_bag_in_binary();
  assert(bag_1.num_elements() == 2046);

  return 0;
}