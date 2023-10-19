#pragma once

#include <Windows.h>

#include "OutputInterface.h"
#include "Constant.h"

class WindowsOutput : OutputInterface {
private:
    HANDLE _WindowsHandle;
    static WindowsOutput* _instance;
    WindowsOutput();
public:
    static WindowsOutput* instance();
    int getTextColor(int colorId, int backgroundColor);
    void setColor(int, int);
    void print(std::string, std::initializer_list<int>) override;
};