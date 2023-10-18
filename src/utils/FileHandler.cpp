#include "FileHandler.h"

json parseJsonFromFile(std::string filename, int &_RETURN_CODE) {
    std::fstream fileHandler(filename);
    json data;
    if(!fileHandler.is_open()) {
        std::cout << "Cannot open file " << filename << std::endl;
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