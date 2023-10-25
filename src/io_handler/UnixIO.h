#pragma once
#include "IOInterface.h"

#if __unix
#include <ncurses.h>
#endif

class UnixIO : public IOInterface {
private:
    inline static UnixIO* _instance = nullptr;
    UnixIO();
public:
    static UnixIO* instance();
    void print(std::string, std::initializer_list<int> attr);
    unsigned char getChar() override;
    void clearScreen() override;

    ~UnixIO();
};