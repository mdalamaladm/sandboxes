#include <iostream>
#include <string>

int main() {
  std::string test {};
  std::cout << "Enter your words: ";
  std::cin >> test;
  // std::getline(std::cin, test);
  std::cout << "1: " << test << '\n';
  std::getline(std::cin, test);
  std::cout << "2: " << test << '\n';
  std::getline(std::cin, test);
  std::cout << "3: " << test << '\n';
  
  return 0;
}