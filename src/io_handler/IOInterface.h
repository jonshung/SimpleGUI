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
     * @param message
     * @param attributes
     * 
     */
    virtual void print(std::string, std::initializer_list<std::string> = {}) = 0;

    /**
     * @brief Base function for translating input key of different OS to a unified definition
     * @param
     * @return 
    */
    virtual int keyTranslate(int) = 0;

    /**
     * @brief Get a character input from keyboard without echoing to the console terminal
     * @return 
    */
    virtual int getChar() = 0;
    virtual void clearScreen() = 0;
};