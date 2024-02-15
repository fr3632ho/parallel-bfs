#include <cassert>
#include <iomanip>
#include <iostream>

#ifndef LOCAL_MAKE
#  include <bag.hpp>
#  include <debug.hpp>
#else
#  include "bag.hpp"
// #  include "debug.hpp"
#endif

pennant_t ::~pennant_t()
{
  // std::cout << "[~pennant_t]" << std::endl;
  if (root != nullptr) {
    clear_pennant(root->left);
    delete root;
  }
}

auto pennant_t ::get_elements(node_t* node, std::vector<int>* elements) -> void
{
  if (node == nullptr) {
    return;
  }
  elements->push_back(node->data);
  get_elements(node->left, elements);
  get_elements(node->right, elements);
}

/**
 * @brief Merge two complete trees of size 2^k to a tree of size 2^(k+1)
 *
 * The resulting, merged, tree will be located in x
 *
 */
auto pennant_t ::merge_pennant(pennant_t* x, pennant_t* y) -> void
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
auto pennant_t ::split_pennant(pennant_t* to_split, pennant_t* remainder)
    -> void
{
  assert(to_split != remainder);
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

auto pennant_t ::get_elements(pennant_t* pennant, std::vector<int>* elements)
    -> void
{
  if (pennant->root == nullptr) {
    return;
  }
  elements->push_back(pennant->root->data);
  get_elements(pennant->root->left, elements);
}

auto pennant_t ::clear_pennant(node_t* r) -> void
{
  if (r == nullptr) {
    return;
  }
  clear_pennant(r->left);
  clear_pennant(r->right);
  delete r;
}

/**
 * @brief Insert an element into bag
 *
 * @param bag
 * @param i
 */
auto pennant_t ::insert(int i) -> void
{
  node_t* t = new node_t;
  t->data = i;
  t->left = nullptr;
  t->right = nullptr;
  size++;
  if (root == nullptr) {
    root = t;
  } else {
    root->left = insert(root->left, t);
  }
}

auto pennant_t ::insert(node_t* r, node_t* t) -> node_t*
{
  if (r == nullptr) {
    return t;
  } else {
    int r_bal = balance(r);
    if (r_bal == 0) {
      if (check(r->right)) {
        r->right = insert(r->right, t);
      } else {
        r->left = insert(r->left, t);
      }
    } else {
      if (check(r->left)) {
        r->left = insert(r->left, t);
      } else {
        r->right = insert(r->right, t);
      }
    }
  }
  return r;
}

auto pennant_t ::check(node_t* r) -> int
{
  // traversing the nodes of the subtree to check any node with balance factor >
  // 0
  if (r == NULL)
    return false;
  bool x = check(r->left);
  if (balance(r))
    return true;
  bool y = check(r->right);

  return x || y;  // If any node present with balance factor > 0
}

auto pennant_t ::balance(node_t* r) -> int
{
  if (r == nullptr)
    return 0;
  int lheight = height(r->left) + 1;
  int rheight = height(r->right) + 1;

  return (lheight - rheight);  //[Balance Factor = Height of Left Sub-Tree -
                               // Height of Right Sub-Tree]
}

auto pennant_t ::height(node_t* r) -> int
{
  if (r == nullptr)
    return 0;
  else {
    int lheight = height(r->left) + 1;
    int rheight = height(r->right) + 1;

    return (lheight > rheight) ? lheight : rheight;  // returns maximum height
  }
}

auto pennant_t ::display_inorder() -> void
{
  std::cout << "\n";
  display_inorder(root, 0);
}

auto pennant_t ::display_inorder(node_t* root, int depth) -> void
{
  const int spaces = 4;

  if (root == nullptr) {
    return;
  }

  display_inorder(root->right, depth + 1);
  std::cout << std::setw(depth * spaces) << "";
  std::cout << root->data << std::endl;
  display_inorder(root->left, depth + 1);
}

bag_t ::bag_t(size_t vertices)
    : size {static_cast<size_t>(log2(vertices) + 1)}
    , number_of_elements(0)
{
  arr = new pennant_t*[size];
  std::memset(arr, 0, size * sizeof(pennant_t*));
}

bag_t ::~bag_t()
{
  {
    // std::cout << "[~ bag called]" << std::endl;
    for (int i = 0; i < size; i++) {
      if (arr[i] != nullptr) {
        delete arr[i];
      }
    }
    delete[] arr;
  }
}

auto bag_t ::insert(int i) -> void
{
  pennant_t* cbt = new pennant_t(i);
  int k = 0;
  while (arr[k] != nullptr && k < size) {
    pennant_t::merge_pennant(cbt, arr[k]);
    arr[k++] = nullptr;
  }
  arr[k] = cbt;
  number_of_elements++;
}

auto bag_t ::get_size() -> size_t
{
  return size;
}

auto bag_t::empty() -> bool
{
  return number_of_elements == 0;
}

/**
 * @brief Insert a pennant into a bag. The pennat must only contain a single
 * node
 *
 * @param pennant
 */
auto bag_t ::insert_pennant(pennant_t* cbt) -> void
{
  int k = 0;
  while (arr[k] != nullptr) {
    pennant_t::merge_pennant(cbt, arr[k]);
    arr[k++] = nullptr;
  }
  arr[k] = cbt;
}

/**
 * @brief Merge the contents of bag into self
 *
 * @param b2
 */
auto bag_t::merge(bag_t* b2) -> void
{
  if (b2 == this)
    return;

  // merge the contents of two bags
  pennant_t* carry = nullptr;
  int r = size, j;  // size should be equal for both bags
  bool A, B, C;
  for (int i = 0; i < r; i++) {
    A = arr[i] != nullptr;
    B = b2->arr[i] != nullptr;
    C = carry != nullptr;
    j = (A * (1 << 2)) | (B * (1 << 1)) | (C * (1));
    switch (j) {
      case 0:
      /* FALL THROUGH */
      case 4:
        break;
      case 1:
        arr[i] = carry;
        carry = nullptr;
        break;
      case 2:
        arr[i] = b2->arr[i];
        b2->arr[i] = nullptr;
        break;
      case 3:
        pennant_t::merge_pennant(carry, b2->arr[i]);
        b2->arr[i] = nullptr;
        break;
      case 5:
        pennant_t::merge_pennant(carry, arr[i]);
        arr[i] = nullptr;
        break;
      case 6:
        /* FALL THROUGH */
      case 7:
        pennant_t::merge_pennant(arr[i], b2->arr[i]);
        b2->arr[i] = nullptr;
        std::swap(arr[i], carry);
        break;
      default:
        break;
    }
  }
  // This will need to be changed
  number_of_elements += b2->number_of_elements;
  b2->number_of_elements = 0;
}
/**
 * @brief Split a bag into two disjoint bags. Some fraction of the items move
 * to the other bag, and the rest of the items remain in the current bag
 *
 * @param other
 */
auto bag_t::split(bag_t* other) -> void
{
  // split the current bag into two disjoint bags
  pennant_t* carry = nullptr;
  bool A, C;
  int r = size - 1, j;
  for (int i = size - 1; i >= 0; i--) {
    A = arr[i] != nullptr;
    C = carry != nullptr;
    j = (A * (1 << 1)) | (C * 1);
    switch (j) {
      case 0:
        break;
      case 1:
        /* FALL THROUGH */
      case 3:
        assert(other->arr[i] == nullptr);
        other->arr[i] = new pennant_t();
        pennant_t::split_pennant(carry, other->arr[i]);
        std::swap(arr[i], carry);
        number_of_elements -= other->arr[i]->size;
        other->number_of_elements += other->arr[i]->size;
        break;
      case 2:
        carry = arr[i];
        arr[i] = nullptr;
        break;
      default:
        break;
    }
  }

  if (carry != nullptr) {
    insert_pennant(carry);
  }
  // number_of_elements = num_elements();
  // other->number_of_elements = other->num_elements();
}

auto bag_t ::num_elements() -> size_t
{
  size_t count = 0;
  for (int i = 0; i < size; i++) {
    if (arr[i] != nullptr) {
      count += 1 << i;
    }
  }
  return count;
}

auto bag_t ::clear() -> void
{
  for (int i = 0; i < size; i++) {
    if (arr[i] != nullptr) {
      delete arr[i];  // this is really slow
      arr[i] = nullptr;
    }
  }
  number_of_elements = 0;
}

auto create(bag_t* b1) -> void {}
auto walk(bag_t* b) -> void {}

/**
 * @brief Get a binary representation of the bag
 * i.e. returns a string of 1's and 0's
 * example of a bag with 19 elements:
 *  \"bag:= 0b010011\"
 *
 *
 */
auto bag_t ::display_bag_in_binary() -> void
{
  std::string out;
  out += "bag := 0b";
  for (int i = size - 1; i >= 0; i--) {
    if (arr[i] != nullptr) {
      out += "1";
    } else {
      out += "0";
    }
  }
  std::cout << out << " number of elements: " << number_of_elements
            << std::endl;
}

/* ITERATOR IMPLEMENTATIONS */
