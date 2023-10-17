#pragma once
#define _CONFIG_UTILITY_

#include "FileHandler.h"
#include <sstream>
#include <iterator>
#include <exception>

class ConfigManager {
private:
    json _rawData;
    string _fileName;
public:
    void loadRaw(string fileName);
    json getRaw(string key);
    ConfigManager();
    ConfigManager(string fileName);
    json get(string key, json obj = json::value_t::null);
};