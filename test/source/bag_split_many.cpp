#include <cassert>
#include <iostream>

#include "bag.hpp"

constexpr size_t number_of_bags = 8;
typedef struct data_t data_t;
struct data_t
{
  bag_t* assign_bag;
  bag_t* merge_bag;
} arr[number_of_bags];

auto split_many(size_t low, size_t high) -> void
{
  if (low == high) {
    return;
  }
  std::cout << "low: " << low << " high: " << high << std::endl;
  size_t mid = (low + high) / 2;
  arr[low].assign_bag->split(arr[mid + 1].assign_bag);
  arr[low].assign_bag->display_bag_in_binary();
  arr[mid + 1].assign_bag->display_bag_in_binary();
  split_many(low, mid);
  split_many(mid + 1, high);
}

auto merge_many() -> void
{
  for (int i = 0; i < number_of_bags; i++) {
    arr[0].merge_bag->merge(arr[i].assign_bag);
  }
}

auto main() -> int
{
  for (int i = 0; i < number_of_bags; i++) {
    arr[i].assign_bag = new bag_t(1024);
    arr[i].merge_bag = new bag_t(1024);
  }
  for (int i = 0; i < 1023; i++) {
    arr[0].assign_bag->insert(i);
  }

  split_many(0, number_of_bags - 1);
  std::cout << "RESULT:" << std::endl;
  for (int i = 0; i < number_of_bags; i++) {
    arr[i].assign_bag->display_bag_in_binary();
  }

  assert(arr[0].assign_bag->number_of_elements == 128);
  assert(arr[1].assign_bag->number_of_elements == 128);
  assert(arr[2].assign_bag->number_of_elements == 128);
  assert(arr[3].assign_bag->number_of_elements == 128);
  assert(arr[4].assign_bag->number_of_elements == 128);
  assert(arr[5].assign_bag->number_of_elements == 128);
  assert(arr[6].assign_bag->number_of_elements == 128);
  assert(arr[7].assign_bag->number_of_elements == 127);

  merge_many();
  std::cout << "MERGE RESULT: " << std::endl;
  for (int i = 0; i < number_of_bags; i++) {
    arr[i].merge_bag->display_bag_in_binary();
  }
  assert(arr[0].merge_bag->number_of_elements == 1023);
  assert(arr[1].merge_bag->number_of_elements == 0);
  assert(arr[2].merge_bag->number_of_elements == 0);
  assert(arr[3].merge_bag->number_of_elements == 0);
  assert(arr[4].merge_bag->number_of_elements == 0);
  assert(arr[5].merge_bag->number_of_elements == 0);
  assert(arr[6].merge_bag->number_of_elements == 0);
  assert(arr[7].merge_bag->number_of_elements == 0);

  return 0;
}