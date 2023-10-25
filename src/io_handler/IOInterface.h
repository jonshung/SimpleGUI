#pragma once

#include <string>
#include <iostream>
#include "Constant.h"

class IOInterface {
private:
public:
    /**
     * @brief Base function for outputing to the desired console window of current output interface
     * 
     * @param std::string msg
     * @param std::initializer_list<int> attributes
     * 
     */
    virtual void print(std::string, std::initializer_list<std::string> = {}) = 0;
    virtual int keyTranslate(int) = 0;
    virtual int getChar() = 0;
    virtual void clearScreen() = 0;
};