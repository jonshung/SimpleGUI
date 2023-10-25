#include <string>
#include <fstream>
#include <iostream>
#include "../libs/json.h"

using nlohmann::json;

enum FileHandlingFlag {
    SUCESS = 0,
    CANNOT_OPEN_FILE = 1
};

json parseJsonFromFile(std::string, int&);