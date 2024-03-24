#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>

#include "Store.h"

using std::endl;

int main(int argc, char **argv) {
  std::cout << "You're openning up a new store in town. Name it: " << endl;

  std::string storeName;

  std::cin >> storeName;

  Store* store = new Store(storeName);

  store->printStoreName();

  delete store;
      
  return EXIT_SUCCESS;
}
