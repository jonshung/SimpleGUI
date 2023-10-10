#include "Utils.h"
#include <iostream>

int getTextColor(int colorId, int backgroundColor) {
    return colorId + backgroundColor * 16;
}

void clearScreen() {
    if (system("CLS")) system("clear");
}

std::string concatenateString(std::initializer_list<std::string> params) {
    std::stringstream result;
    for(auto i : params) result << i;
    return result.str();
}