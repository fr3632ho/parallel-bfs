#include <cassert>
#include <iomanip>
#include <iostream>

#include "bag.hpp"

#include "debug.hpp"

pennant_t ::~pennant_t()
{
  std ::cout << "[deleting pennant]" << std ::endl;
  if (root != nullptr) {
    clear_pennant(root->left);
    delete root;
  }
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

auto insert(bag_t* bag, int i) -> void
{
  pennant_t* cbt = new pennant_t(i);
  int k = 0;
  while (bag->arr[k] != nullptr) {
    pennant_t::merge_pennant(cbt, bag->arr[k]);
    bag->arr[k++] = nullptr;
  }
  bag->arr[k] = cbt;
}

auto insert_pennant(bag_t* bag, pennant_t* cbt) -> void
{
  int k = 0;
  while (bag->arr[k] != nullptr) {
    pennant_t::merge_pennant(cbt, bag->arr[k]);
    bag->arr[k++] = nullptr;
  }
  bag->arr[k] = cbt;
}

auto merge(bag_t* b1, bag_t* b2) -> void
{
  // merge the contents of two bags
  pennant_t* carry = nullptr;
  int r = b1->size, j;  // size should be equal for both bags
  bool A, B, C;
  for (int i = 0; i < r; i++) {
    A = b1->arr[i] != nullptr;
    B = b2->arr[i] != nullptr;
    C = carry != nullptr;
    j = (A * (1 << 2)) | (B * (1 << 1)) | (C * (1));
    LOGF("j = %d\n", j);
    assert(j < 8 && j >= 0);
    switch (j) {
      case 0:
      /* FALL THROUGH */
      case 4:
        LOGF("case 0 or 4, nothing\n");
        break;
      case 1:
        b1->arr[i] = carry;
        carry = nullptr;
        LOGF("case 1, swap(A, C)\n");
        break;
      case 2:
        b1->arr[i] = b2->arr[i];
        b2->arr[i] = nullptr;
        LOGF("case 2, swap(A, B)\n");
        break;
      case 3:
        pennant_t::merge_pennant(carry, b2->arr[i]);
        b2->arr[i] = nullptr;
        assert(carry->size == (1 << (i + 1)));
        LOGF("case 3, merge(C, B)\n");
        break;
      case 5:
        pennant_t::merge_pennant(carry, b1->arr[i]);
        b1->arr[i] = nullptr;
        assert(carry->size == (1 << (i + 1)));
        LOGF("case 5, merge(C, A)\n");
        break;
      case 6:
        /* FALL THROUGH */
      case 7:
        pennant_t::merge_pennant(b1->arr[i], b2->arr[i]);
        b2->arr[i] = nullptr;
        std::swap(b1->arr[i], carry);
        LOGF("case 6 or 7, merge(A, B) and swap(A, C)\n");
        break;
      default:
        break;
    }
  }
}

auto create(bag_t* b1) -> void {}

auto split(bag_t* current, bag_t* other) -> void
{
  // split the current bag into two disjoint bags
  pennant_t* carry = nullptr;
  bool A, C;
  int r = current->size - 1, j;
  for (int i = current->size - 1; i >= 0; i--) {
    A = current->arr[i] != nullptr;
    C = carry != nullptr;
    j = (A * (1 << 1)) | (C * 1);
    assert(j < 4 && j >= 0);
    LOGF("j = %d, A = %d, C = %d\n", j, A, C);
    switch (j) {
      case 0:
        LOGF("case 0, nothing\n");
        break;
      case 1:
        /* FALL THROUGH */
      case 3:
        LOGF("case 1 or 3, split(C,B); swap(C, A)\n");
        assert(other->arr[i] == nullptr);
        other->arr[i] = new pennant_t();
        pennant_t::split_pennant(carry, other->arr[i]);
        std::swap(current->arr[i], carry);
        break;
      case 2:
        LOGF("case 2, swap(A, C)\n");
        carry = current->arr[i];
        current->arr[i] = nullptr;
        break;
      default:
        break;
    }
  }

  if (carry != nullptr) {
    insert_pennant(current, carry);
  }
}

auto walk(bag_t* b) -> void {}

auto display_bag_in_binary(bag_t* bag) -> void
{
  std::string out;
  out += "bag := 0b";
  for (int i = bag->size - 1; i >= 0; i--) {
    if (bag->arr[i] != nullptr) {
      out += "1";
    } else {
      out += "0";
    }
  }
  std::cout << out << std::endl;
}