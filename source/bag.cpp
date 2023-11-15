#include <iomanip>
#include <iostream>

#include "bag.hpp"

pennant_t ::~pennant_t()
{
  std ::cout << "[deleting pennant]" << std ::endl;
  if (root != nullptr) {
    clear_tree(root->left);
    delete root;
  }
}

auto pennant_t ::clear_tree(node_t* r) -> void
{
  if (r == nullptr) {
    return;
  }
  clear_tree(r->left);
  clear_tree(r->right);
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
    pennant_t::merge_tree(cbt, bag->arr[k]);
    bag->arr[k++] = nullptr;
  }
  bag->arr[k] = cbt;
}

auto merge(bag_t* b1, bag_t* b2) -> void {}

auto create(bag_t* b1) -> void {}

auto split(bag_t* current, bag_t* other) -> void {}

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