#include "UserOrderHandler.h"

void UserOrder::addOrder(std::shared_ptr<StockType> order) {
    _orders.push_back(order);
}

std::vector<std::shared_ptr<StockType>>& UserOrder::getOrders() {
    return this->_orders;
}

std::shared_ptr<StockType> UserOrder::pop() {
    std::shared_ptr<StockType> lastItem = _orders.back();
    _orders.pop_back();
    return lastItem;
}

void UserOrder::clear() {
    _orders.clear();
}