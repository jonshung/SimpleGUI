#pragma once
#define _STOCK_TYPE_H

#include <string>

class StockType {
private:
    std::string _stockName;
public:
    inline StockType(std::string vl = "") {
        _stockName = vl;
    }
    inline std::string stock() {
        return _stockName;
    }
    virtual std::string toString() = 0;
};