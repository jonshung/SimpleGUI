#include "DrinkType.h"

DrinkType::DrinkType(std::string vl) : StockType(vl) {}

std::string DrinkType::toString() {
    return "Drink";
}