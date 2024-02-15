#ifndef BAG_HPP
#define BAG_HPP

#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <iterator>
#include <vector>

typedef struct node_t node_t;

struct node_t
{
  int data;
  node_t *left, *right;
};

class pennant_t
{
private:
  node_t* root;

  auto height(node_t*) -> int;
  auto balance(node_t*) -> int;
  auto check(node_t*) -> int;
  auto insert(node_t*, node_t*) -> node_t*;
  auto display_inorder(node_t* root, int depth) -> void;
  auto clear_pennant(node_t*) -> void;
  auto empty() -> bool;

  static auto get_elements(node_t* node, std::vector<int>* elements) -> void;

public:
  struct Iterator
  {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = int;
    using pointer = node_t*;
    using pointer_data = int*;
    using reference = int&;

    Iterator(pointer root)
        : current {root}
        , right_most {nullptr}
    {
      ptr = next();
    }

    reference operator*() { return ptr->data; }
    pointer_data operator->() { return &ptr->data; }

    Iterator& operator++()
    {
      ptr = next();
      return *this;
    }
    Iterator operator++(int)
    {
      Iterator temp = *this;
      ptr = next();
      return temp;
    }

    friend bool operator==(const Iterator& a, const Iterator& b)
    {
      return a.ptr == b.ptr;
    }
    friend bool operator!=(const Iterator& a, const Iterator& b)
    {
      return a.ptr != b.ptr;
    }

  private:
    pointer next()
    {
      if (current == nullptr) {
        return nullptr;
      }

      pointer temp;
      if (current->left == nullptr) {
        temp = current;
        current = current->right;
        return temp;
      }

      right_most = current->left;
      while (right_most->right != nullptr && right_most->right != current) {
        right_most = right_most->right;
      }

      if (right_most->right == NULL) {
        right_most->right = current;
        current = current->left;
      } else {
        right_most->right = nullptr;
        temp = current;
        current = current->right;
        return temp;
      }
      return next();
    }

    pointer start, ptr, current, right_most;
  };

  Iterator begin() { return Iterator {root}; }
  Iterator end() { return Iterator {nullptr}; }

  size_t size;

  pennant_t()
      : root {nullptr}
      , size {0}
  {
  }

  pennant_t(int i)
      : size {1}
  {
    root = new node_t;
    root->data = i;
    root->left = nullptr;
    root->right = nullptr;
  }
  ~pennant_t();

  auto display_inorder() -> void;
  auto insert(int i) -> void;
  static auto merge_pennant(pennant_t* x, pennant_t* y) -> void;
  static auto split_pennant(pennant_t* to_split, pennant_t* remainder) -> void;
  static auto get_elements(pennant_t* pennant, std::vector<int>* elements)
      -> void;
};

/**
 * @brief bag structure
 *
 * will contain complete binary trees in an array. The bag has a fixed size with
 * a maximum capacity of N
 *
 * The bag will be represented as trees of size:
 * [2^0, 2^1, 2^2, ..., 2^(N-1)]
 */
class alignas(64) bag_t
{
private:
  /* Variables */

public:
  bag_t(size_t vertices);
  // bag_t(const bag_t& other);
  // bag_t(bag_t&& other);
  ~bag_t();

  auto empty() -> bool;
  auto get_size() -> size_t;
  auto insert_pennant(pennant_t* pennant) -> void;
  auto insert(int i) -> void;
  auto merge(bag_t* bag_2) -> void;
  auto split(bag_t* other) -> void;
  auto display_bag_in_binary() -> void;
  auto num_elements() -> size_t;
  auto clear() -> void;
  auto operator[](size_t index) -> pennant_t* { return arr[index]; }

  size_t size;
  size_t number_of_elements;
  pennant_t** arr;
  char padding[40];
};

/**
 * @brief Create an empty bag
 *
 * @param bag_1
 */
auto create(bag_t* bag_1) -> void;

/**
 * @brief Walk the bag structure, visiting every element
 *
 * @param bag
 */
auto walk(bag_t* bag) -> void;

#endif