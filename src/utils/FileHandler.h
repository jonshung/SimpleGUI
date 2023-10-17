#include <string>
#include <fstream>
#include <iostream>
#include "src/libs/json.hpp"

using nlohmann::json;
using std::string;

enum FileHandlingFlag {
    SUCESS = 0,
    CANNOT_OPEN_FILE = 1
};

json parseJsonFromFile(string filename, int &_RETURN_CODE);