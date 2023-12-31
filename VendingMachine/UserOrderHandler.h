#pragma once
#define _USER_ORDER_HANDLER_

#include <fstream>
#include <vector>
#include <string>
#include "Constant.h"
#include "GeneralUtils.h"
#include "StockType.h"
#include <memory>

class UserOrder {
private:
    std::vector<std::shared_ptr<StockType>> _orders;
public:
    std::vector<std::shared_ptr<StockType>>& getOrders();
    void addOrder(std::shared_ptr<StockType>);
    std::shared_ptr<StockType> pop();
    void clear();
};