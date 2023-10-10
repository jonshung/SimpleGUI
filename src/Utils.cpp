#include "Utils.h"
#include <iostream>

/**
 * @brief Get the Text Color with offset respect to current background color
 * 
 * @param colorId 
 * @param backgroundColor 
 * @return int 
 */
int getTextColor(int colorId, int backgroundColor) {
    return colorId + backgroundColor * 16;
}

/**
 * @brief Clear the screen
 * 
 */
void clearScreen() {
    if (system("CLS")) system("clear");
}

/**
 * @brief Concatenate a group of strings
 * 
 * @param params 
 * @return std::string 
 */
std::string concatenateString(std::initializer_list<std::string> params) {
    std::stringstream result;
    for(auto i : params) result << i;
    return result.str();
}