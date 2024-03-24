#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>

using std::endl;


class Store {
  public:
    std::string name;
    int currentMoney;
    int dailyRevenue;

    Store(std::string Name) {
      this->name = Name;
      this->currentMoney = 0;
      this->dailyRevenue = 10;

      std::cout << "Your own " << name << " is now open!" << endl;
      std::cout << "Enjoy the game!" << endl;
    }
    
    void printStoreName() {
      std::cout << name << " Gold: " << currentMoney << std::endl;
    };
};

int main(int argc, char **argv) {
  std::cout << "You're openning up a new store in town. Name it: " << endl;

  std::string storeName;

  std::cin >> storeName;

  Store* store = new Store(storeName);

  store->printStoreName();

  delete store;
      
  return EXIT_SUCCESS;
}
