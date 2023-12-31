#pragma once
#define _CONFIG_UTILITY_

#include "FileHandler.h"
#include <sstream>
#include <iterator>
#include <exception>
#include <string.h>
#include <algorithm>
#include <iterator>
#include <iomanip>

class ConfigManager {
protected:
    std::string _fileName;
    json _rawData;
public:
    void loadFromFile(std::string, json = json());
    template<typename T>
    T get(std::string, json = json::value_t::null);
    ConfigManager();
    ConfigManager(std::string, json = json());
    json getRaw(std::string, json = json::value_t::null);
    ~ConfigManager();
};