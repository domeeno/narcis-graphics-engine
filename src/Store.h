#ifndef STORE_H
#define STORE_H

#include <string>

class Store {
  public:
    std::string name;
    int currentMoney;
    int dailyRevenue;

    Store(std::string Name);
    
    void printStoreName();

  private:
    // NONE
};

#endif //STORE_H
