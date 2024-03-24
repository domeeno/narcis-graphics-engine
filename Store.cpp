#include "Store.h"

#include <string>
#include <iostream>

Store::Store(std::string Name) {
  this->name = Name;
  this->currentMoney = 0;
  this->dailyRevenue = 10;

  std::cout << "Your own " << this->name << " is now open!" << std::endl;
  std::cout << "Enjoy the game!" << std::endl;
};

void Store::printStoreName() {
  std::cout << this->name << " Gold: " << this->currentMoney << std::endl;
};
