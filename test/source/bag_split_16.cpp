#include <cassert>
#include <iostream>

#include "bag.hpp"

auto main() -> int
{
  bag_t bag_1(100), bag_2(100);
  for (int i = 0; i < 16; i++) {
    bag_1.insert(i);
  }

  std::cout << "Bag 1 size: " << bag_1.num_elements() << std::endl;
  std::cout << "Bag 2 size: " << bag_2.num_elements() << std::endl;
  bag_1.split(&bag_2);

  bag_1.display_bag_in_binary();
  bag_2.display_bag_in_binary();
  std::cout << "Bag 1 size: " << bag_1.num_elements() << std::endl;
  std::cout << "Bag 2 size: " << bag_2.num_elements() << std::endl;
  assert(bag_1.num_elements() == bag_2.num_elements());
  assert(bag_1.num_elements() == 8);

  return 0;
}