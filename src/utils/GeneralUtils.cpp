#include "GeneralUtils.h"
#include <iostream>

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