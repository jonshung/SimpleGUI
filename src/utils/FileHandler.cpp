#include "FileHandler.h"

/**
 * @brief Parse a file into nlohmann::json object
 * 
 * @param filename 
 * @param _RETURN_CODE 
 * @return 
*/
json parseJsonFromFile(std::string filename, int &_RETURN_CODE) {
    std::fstream fileHandler(filename);
    json data;
    if(!fileHandler.is_open()) {
        _RETURN_CODE = FileHandlingFlag::CANNOT_OPEN_FILE;
        return data;
    }

    try {
        data = json::parse(fileHandler);
    } catch (const json::parse_error& e) {
        std::cout << e.what() << std::endl;
    }
    _RETURN_CODE = FileHandlingFlag::SUCESS;
    return data;
}

/**
* @todo: Add file serialization and file output
*/