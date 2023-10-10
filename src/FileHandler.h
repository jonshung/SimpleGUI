#include <string>
#include <fstream>
#include <iostream>
#include "libs/json.hpp"

enum FileHandlingFlag {
    SUCESS = 0,
    CANNOT_OPEN_FILE = 1
};

nlohmann::json parseJsonFromFile(std::string filename, int &_RETURN_CODE);