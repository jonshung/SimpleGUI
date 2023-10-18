#include "UserOrderHandler.h"

void UserOrder::addOrder(int orderId) {
    _orders.push_back(orderId);
}

std::vector<int>& UserOrder::getOrders() {
    return this->_orders;
}

int UserOrder::pop() {
    int lastItem = _orders.back();
    _orders.pop_back();
    return lastItem;
}

void UserOrder::clear() {
    _orders.clear();
}

/**
 * @brief Get the Product Name From ProductId
 *        Hard coded for example
 * 
 * @param id 
 * @return std::string 
 */
std::string UserOrder::getProductNameFromId(int id) {
    if(id > 6 || id < 0) return "";
    if(id <= 3) {
        return concatenateString({"Snack ", std::to_string(id + 1)});
    }
    return concatenateString({"Drink ", std::to_string(id - 3)});
}