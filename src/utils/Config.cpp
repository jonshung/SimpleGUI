#include "Config.h"

/**
 * @brief Initialize an empty config interface
*/
ConfigManager::ConfigManager() {
    this->_rawData = json();
    this->_fileName = "";
}

/**
 * @brief Initialize a config interface
 * @param fileName 
*/
ConfigManager::ConfigManager(std::string fileName, json defaultFallback) {
    this->loadFromFile(fileName, defaultFallback);
}

/**
 * @brief Load a config file from path relative to executable's path
 * @param fileName
*/
void ConfigManager::loadFromFile(std::string fileName, json defaultFallback) {
    int returnCode;
    this->_fileName = fileName;
    json buffer = parseJsonFromFile(fileName, returnCode);
    if (returnCode != FileHandlingFlag::SUCESS) {
        this->_rawData = defaultFallback;
        return;
    }
    this->_rawData = buffer;
}

/**
 * @brief Get the raw nlohmann::json object value if it exists, else throw an error for undefined key
 * @param key 
 * @param obj 
 * @return 
*/
json ConfigManager::getRaw(std::string key, json obj) {
    if (obj.is_null()) obj = _rawData;
    json jsonValue;
    try {
        jsonValue = obj[key];
    }
    catch (const json::invalid_iterator& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return -1;
    }
    return jsonValue;
}

/**
 * @brief return the type-casted value from the config interface
 * @tparam T 
 * @param key 
 * @param obj 
 * @return 
*/
template<typename T>
T ConfigManager::get(std::string key, json obj) {
    if (obj.is_null()) obj = _rawData;
    T returnType;
    try {
        json parsedValue = obj[key];
        returnType = parsedValue.get<T>();
    }
    catch (const json::invalid_iterator& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return returnType;
}

ConfigManager::~ConfigManager() {
    if(this->_fileName.length() == 0) return;
    std::fstream fH(this->_fileName, std::fstream::out);
    if(!fH.is_open()) return;
    fH << std::setw(4) << this->_rawData.dump(); 
}

/**
 * @brief Pre-defined template for ConfigManager::get<T>
*/
template int ConfigManager::get<int>(std::string key, json obj);
template bool ConfigManager::get<bool>(std::string key, json obj);
template std::string ConfigManager::get<std::string>(std::string key, json obj);
template json ConfigManager::get<json>(std::string key, json obj);
template std::vector<std::string> ConfigManager::get<std::vector<std::string> >(std::string key, json obj);
template std::vector<int> ConfigManager::get<std::vector<int> >(std::string key, json obj);
template std::vector<bool> ConfigManager::get<std::vector<bool> >(std::string key, json obj);