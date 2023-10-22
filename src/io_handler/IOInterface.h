#pragma once

#include <string>
#include <iostream>

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
    virtual void print(std::string, std::initializer_list<int>) = 0;
    virtual unsigned char getChar() = 0;
    virtual void clearScreen() = 0;
};