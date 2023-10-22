#include "IOInterface.h"

#pragma once

#ifndef _LINUX
#error OS Identification failed
#endif

#include <ncurses/ncurses.h>

class UnixIO : public IOInterface {
private:
    static UnixIO* _instance;
    UnixIO();
public:
    static UnixIO* instance();
    void print(std::string, std::initializer_list<int> attr);
    unsigned char getChar() override;
    void clearScreen() override;

    ~UnixIO();
};