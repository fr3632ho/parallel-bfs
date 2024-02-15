#include <cassert>
#include <iostream>

#include "bag.hpp"

auto main() -> int
{
  bag_t bag_1(1024), bag_2(1024);
  for (int i = 0; i < 1023; i++) {
    bag_1.insert(i);
  }

  std::cout << "Bag 1 size: " << bag_1.num_elements() << std::endl;
  std::cout << "Bag 2 size: " << bag_2.num_elements() << std::endl;
  bag_1.split(&bag_2);

  bag_1.display_bag_in_binary();
  bag_2.display_bag_in_binary();
  std::cout << "Bag 1 size: " << bag_1.num_elements() << std::endl;
  std::cout << "Bag 2 size: " << bag_2.num_elements() << std::endl;
  assert(bag_1.num_elements() != bag_2.num_elements());
  assert(bag_1.num_elements() == 512);
  assert(bag_2.num_elements() == 511);

  bag_t bag_3(1024);
  std::cout << "Bag 2 size: " << bag_2.num_elements() << std::endl;
  std::cout << "Bag 3 size: " << bag_3.num_elements() << std::endl;
  bag_2.split(&bag_3);
  std::cout << "Bag 2 size: " << bag_2.num_elements() << std::endl;
  std::cout << "Bag 3 size: " << bag_3.num_elements() << std::endl;
  bag_2.display_bag_in_binary();
  bag_3.display_bag_in_binary();
  assert(bag_2.num_elements() != bag_3.num_elements());
  assert(bag_2.num_elements() == 256);
  assert(bag_3.num_elements() == 255);
  return 0;
}