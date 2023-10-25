#pragma once

#if _WIN32
#include <Windows.h>
#include <conio.h>
#endif

#include "IOInterface.h"
#include "Constant.h"

// Explicit reserved keyword definition, only applies to OS other than Win32
#ifndef HANDLE
#define HANDLE void*
#endif

namespace WindowsKeys {
    enum {
        Numpad = 0,
        Arrow = 224,
        Up = 72,
        Down = 80,
        Left = 75,
        Right = 77,
        EscapeKey = 27,
        Enter = 13,
        Del = 83
    };
};

class WindowsIO : public IOInterface {
private:
    HANDLE _WindowsHandle;
    static WindowsIO* _instance;
    WindowsIO();
public:
    static WindowsIO* instance();
    int getTextColor(int colorId, int backgroundColor);
    void setColor(int, int);
    void print(std::string, std::initializer_list<std::string> = {}) override;
    int getChar() override;
    int keyTranslate(int);
    void clearScreen() override;
};