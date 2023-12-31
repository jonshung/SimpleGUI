#pragma once

#include "libs/json.hpp"
#include <filesystem>
#include <fstream>

using namespace nlohmann;

class StockHandler {
private:
    ordered_json _stocks;
    std::string _filepath;
public:
    ordered_json& stocks();
    StockHandler(std::string = ".VMStock.json");
    void defaultInit();
    void save(std::string);
    ~StockHandler();
};