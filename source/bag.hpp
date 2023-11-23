#pragma once

#include <cassert>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <vector>

typedef struct bag_t bag_t;
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
  // size_t element_count;

  auto height(node_t*) -> int;
  auto balance(node_t*) -> int;
  auto check(node_t*) -> int;
  auto insert(node_t*, node_t*) -> node_t*;
  auto display_inorder(node_t* root, int depth) -> void;
  auto clear_pennant(node_t*) -> void;
  auto empty() -> bool;

  static auto get_elements(node_t* node, std::vector<int>* elements) -> void
  {
    if (node == nullptr) {
      return;
    }
    elements->push_back(node->data);
    get_elements(node->left, elements);
    get_elements(node->right, elements);
  }

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

  Iterator begin() { return Iterator(root); }
  Iterator end() { return Iterator(nullptr); }

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
  /**
   * @brief Merge two complete trees of size 2^k to a tree of size 2^(k+1)
   *
   * The resulting, merged, tree will be located in x
   *
   */
  static auto merge_pennant(pennant_t* x, pennant_t* y) -> void
  {
    if (x == nullptr) {
      x = y;
      // y = x;
      return;
    }
    if (y == nullptr) {
      return;
    }

    y->root->right = x->root->left;
    x->root->left = y->root;
    x->size += y->size;

    y->size = 0;
    y->root = nullptr;
    delete y;  // this can be done better, think if we should add a free list?
  }

  /**
   * @brief Split pennant to_split, taking the leaving the left subtree and
   * moving the right to the remainder. to_split has to be a valid pointer with
   * a root != nullptr
   *
   * @param to_split
   * @param remainder an empty pennant that will be filled
   */
  static auto split_pennant(pennant_t* to_split, pennant_t* remainder) -> void
  {
    assert(to_split != nullptr);
    if (to_split->root->left == nullptr) {
      return;
    }
    assert(to_split->root != nullptr);
    node_t* lroot = to_split->root->left;
    if (lroot != nullptr) {
      remainder->root = lroot;
      to_split->root->left = lroot->left;
      lroot->left = lroot->right;
      lroot->right = nullptr;

      size_t new_size = to_split->size >> 1;
      remainder->size = new_size;
      to_split->size = new_size;
    }
  }

  static auto get_elements(pennant_t* pennant, std::vector<int>* elements)
      -> void
  {
    if (pennant->root == nullptr) {
      return;
    }
    elements->push_back(pennant->root->data);
    get_elements(pennant->root->left, elements);
  }
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
struct bag_t
{
  /**
   * @brief Construct a new bag t object
   *
   * @param vertices Number of vertices that the bag can contain maximum,
   * vertices needs to be a positive integer > 0
   */
  bag_t(size_t vertices)
      : size {static_cast<size_t>(log2(vertices) + 1)}
      , number_of_elements {0}
  {
    arr = new pennant_t*[size];
  }

  ~bag_t()
  {
    for (int i = 0; i < size; i++) {
      if (arr[i] != nullptr) {
        delete arr[i];
      }
    }
    delete[] arr;
  }

  auto num_elements() -> size_t
  {
    size_t count = 0;
    for (int i = 0; i < size; i++) {
      if (arr[i] != nullptr) {
        count += 1 << i;
      }
    }
    return count;
  }

  auto empty() -> bool;

  struct Iterator
  {
    using iterator_type = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = int;
    using pointer_data = int*;
    using reference = int&;
    using pointer = pennant_t*;
    using pennant_pointer = pennant_t::Iterator;

    Iterator(pointer bag_start);

  private:
    pointer current;
  };

  /* Variables */
  size_t size;
  size_t number_of_elements;
  pennant_t** arr;
};

/**
 * @brief Insert a pennant into a bag. The pennat must only contain a single
 * node
 *
 * @param pennant
 * @param i
 */
auto insert_pennant(bag_t* bag, pennant_t* pennant) -> void;

/**
 * @brief Insert an element into a bag
 *
 * @param bag
 * @param i
 */
auto insert(bag_t* bag, int i) -> void;

/**
 * @brief Merge the contents of bag b2 into bag b1
 *
 * @param bag_1
 * @param bag_2
 */
auto merge(bag_t* bag_1, bag_t* bag_2) -> void;

/**
 * @brief Create an empty bag
 *
 * @param bag_1
 */
auto create(bag_t* bag_1) -> void;

/**
 * @brief Split a bag into two disjoint bags. Some fraction of the items move to
 * the other bag, and the rest of the items remain in the current bag
 *
 * @param current
 * @param other
 */
auto split(bag_t* current, bag_t* other) -> void;

/**
 * @brief Walk the bag structure, visiting every element
 *
 * @param bag
 */
auto walk(bag_t* bag) -> void;

/**
 * @brief Get a binary representation of the bag
 * i.e. returns a string of 1's and 0's
 * example of a bag with 19 elements:
 *  \"bag:= 0b010011\"
 *
 *
 * @param bag
 */
auto display_bag_in_binary(bag_t* bag) -> void;