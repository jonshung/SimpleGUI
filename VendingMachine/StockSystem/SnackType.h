#pragma once
#define _SNACK_TYPE_H
#include "StockType.h"

class SnackType : public StockType {
private:
    std::string _stockName;
public:
    SnackType(std::string = "Snack");
    std::string toString() override;
};