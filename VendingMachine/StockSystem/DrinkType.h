#pragma once
#define _DRINK_TYPE_H
#include "StockType.h"

class DrinkType : public StockType {
public:
    DrinkType(std::string = "Snack");
    std::string toString() override;
};