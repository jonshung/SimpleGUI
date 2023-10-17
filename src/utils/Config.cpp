#include "Config.h"

ConfigManager::ConfigManager() {
    this->_rawData = json();
    this->_fileName = "";
}

ConfigManager::ConfigManager(string fileName) {
    this->loadRaw(fileName);
}

void ConfigManager::loadRaw(string fileName) {
    int returnCode;
    json buffer = parseJsonFromFile(fileName, returnCode);
    if (returnCode != FileHandlingFlag::SUCESS) {
        std::cout << "Unable to process raw from " << fileName << std::endl;
        return;
    }
    this->_rawData = buffer;
    this->_fileName = fileName;
}

json ConfigManager::get(string key, json obj) {
    if(obj.is_null()) obj = _rawData;
    json returnType;
    try {
        returnType = obj[key];
    } catch (const json::invalid_iterator& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return -1;
    }
    return returnType;
}