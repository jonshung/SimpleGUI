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

class WindowsIO : public IOInterface {
private:
    HANDLE _WindowsHandle;
    static WindowsIO* _instance;
    WindowsIO();
public:
    static WindowsIO* instance();
    int getTextColor(int colorId, int backgroundColor);
    void setColor(int, int);
    void print(std::string, std::initializer_list<int>) override;
    unsigned char getChar() override;
    void clearScreen() override;
};