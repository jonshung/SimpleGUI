#pragma once
#include "IOInterface.h"

#if __unix
#include <termios.h>
#endif

namespace UnixKeys {
    enum {
        Up = 65,
        Down = 66,
        Right = 67,
        Left = 68,
        EscapeKey = 27,
        Enter = 10,
        Del = 14
    };
};

class UnixIO : public IOInterface {
private:
    inline static UnixIO* _instance = nullptr;
    #if __unix
    termios _term;
    #endif
    UnixIO();
public:
    static UnixIO* instance();
    void print(std::string, std::initializer_list<std::string> = {});
    void noEcho();
    void echo();
    int getChar() override;
    int keyTranslate(int);
    void clearScreen() override;

    ~UnixIO();
};