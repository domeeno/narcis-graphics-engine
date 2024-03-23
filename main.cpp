#include <cstdlib>
#include <iostream>
#include <string>

int main(int argc, char **argv) {

  std::cout << "You're openning up a new store in town. Name it: " << std::endl;

  std::string storeName;
    
  std::cin >> storeName;

  std::cout << "Your own " << storeName << " is now open!" << std::endl;
  std::cout << "Enjoy the game!" << std::endl;

  return EXIT_SUCCESS;
}
