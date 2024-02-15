#include <iostream>

#include "bag.hpp"

#define MAIN
#ifdef MAIN

int main()
{
  pennant_t cbt;
  bag_t* bag = nullptr;
  int ch, n;
pennant_test:;
  do {
    std::cout << "\n\n\t| Pennant Test |\n";
    std::cout << "\n1.Create of size N:";
    std::cout << "\n2.Insert";
    std::cout << "\n3.Display";
    std::cout << "\n4.Bag Test";
    std::cout << "\n5.Exit\n";
    std::cin >> ch;
    switch (ch) {
      case 1:
        int n;
        std::cout << "\nEnter the total number of elements : ";
        std::cin >> n;
        if (n > 0) {
          for (int i = 1; i < n + 1; i++) {
            cbt.insert(i);
          }
        }
        break;
      case 2:
        cbt.insert(ch);
        break;
      case 3:
        cbt.display_inorder();
        break;
      case 4:
        goto bag_test;
      case 5:
        goto exit_prog;
      default:
        break;
    }
  } while (ch != 4);

bag_test:;
  do {
    std::cout << "\n\n\t| Bag Test |\n";
    std::cout << "\n0.Create EMPTY bag of size N:";
    std::cout << "\n1.Create FULL of size N:";
    std::cout << "\n2.Insert one element";
    std::cout << "\n3.Display binary bag";
    std::cout << "\n4.Display Bag & Pennants";
    std::cout << "\n5.Clear bag";
    std::cout << "\n6.Pennant Test";
    std::cout << "\n7.Exit\n";
    std::cin >> ch;
    switch (ch) {
      case 0:
        if (bag != nullptr) {
          std::cout << "Clearing old bag!" << std::endl;
          delete bag;
          bag = nullptr;
        }
        std::cout << "\nEnter the total number of elements: ";
        std::cin >> n;
        if (n > 0) {
          bag = new bag_t(n);
        } else {
          std::cout << "Invalid input!" << std::endl;
        }
        break;
      case 1:
        if (bag != nullptr) {
          std::cout << "Clearing old bag!" << std::endl;
          delete bag;
          bag = nullptr;
        }
        std::cout << "\nEnter the total number of elements: ";
        std::cin >> n;
        if (n > 0) {
          bag = new bag_t(n);
          for (int i = 1; i < n + 1; i++) {
            bag->insert(i);
          }
        } else {
          std::cout << "Invalid input!" << std::endl;
        }
        break;
      case 2:
        if (bag == nullptr) {
          std::cout << "Create a bag first!" << std::endl;
          break;
        }
        bag->insert(1);
        bag->display_bag_in_binary();
        break;
      case 3:
        bag->display_bag_in_binary();
        break;
      case 4:
        if (bag == nullptr) {
          std::cout << "Create a bag first!" << std::endl;
          break;
        }
        bag->display_bag_in_binary();
        size_t count = bag->get_size();
        for (int i = count - 1; i >= 0; i--) {
          if (bag->arr[i] != nullptr) {
            bag->arr[i]->display_inorder();
          }
        }
        break;
      case 5:
        if (bag == nullptr) {
          std::cout << "Can't clear uninitialized bag!" << std::endl;
          break;
        }

        for (int i = 0; i < bag->size; i++) {
          if (bag->arr[i] != nullptr) {
            std::cout << "Clearing index [" << i << "]" << std::endl;
            delete bag->arr[i];
          }
          bag->arr[i] = nullptr;
        }
        break;
      case 6:
        goto pennant_test;
        break;
      case 7:
        goto exit_prog;
      default:
        break;
    }
  } while (ch != 7);

exit_prog:;
  return 0;
}

#endif