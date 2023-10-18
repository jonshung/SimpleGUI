#pragma once
#define _USER_ORDER_HANDLER_

#include <fstream>
#include <vector>
#include <string>
#include "Constant.h"
#include "GeneralUtils.h"

enum ProductsID {
    SNACK1 = 0,
    SNACK2 = 1,
    SNACK3 = 2,
    SNACK4 = 3,
    DRINK1 = 4,
    DRINK2 = 5,
    DRINK3 = 6,
};

class UserOrder {
private:
    std::vector<int> _orders;
public:
    std::vector<int>& getOrders();
    void addOrder(int orderId);
    int pop();
    void clear();

    static std::string getProductNameFromId(int id);
};