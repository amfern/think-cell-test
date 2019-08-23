#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

#include "include/hello.hpp"

int main(int argc, char* argv[])
{
  printHello();
  // suppress warnings
  (void)argc; (void)argv;

  std::cout << "Hello World!" << std::endl;

  // Create a list containing integers
  std::vector<int> v{0, 1, 2, 3, 4};

  // Add an integer to the back of the list
  v.push_back(13);

  // Insert an integer before 16 by searching
  auto it = std::find(v.begin(), v.end(), 3);
  if (it != v.end()) {
    v.insert(it, 42);
  }

  // Iterate and print values of the list
  for (int n : v) {
    std::cout << n << '\n';
  }
  return 0;
}
