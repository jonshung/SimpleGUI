#include "WindowsIO.h"

// initialize instance pointer
WindowsIO* WindowsIO::_instance = nullptr;

WindowsIO::WindowsIO() {
    _WindowsHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}

/**
 * @brief Get the Text Color with offset respect to current background color
 * 
 * @param colorId 
 * @param backgroundColor 
 * @return int 
 */
int WindowsIO::getTextColor(int colorId, int backgroundColor) {
    return colorId + backgroundColor * 16;
}

/**
 * @brief Set current text color
 *
 * @param colorId
 */
void WindowsIO::setColor(int bgColor, int colorId) {
    int colorOffset = getTextColor(colorId, bgColor);
    SetConsoleTextAttribute(_WindowsHandle, colorId);
}

WindowsIO* WindowsIO::instance() {
    if (_instance == nullptr) {
        _instance = new WindowsIO();
    }
    return _instance;
}

void WindowsIO::print(std::string msg, std::initializer_list<int> attr) {
    int bgColor = Color::BLACK;
    int color = Color::WHITE;
    int defaultBgColor = Color::BLACK;
    int defaultColor = Color::WHITE;
    if(attr.size() > 0) {
        color = *(attr.begin());
        if(attr.size() > 1) {
            int vl = *(attr.begin() + 1);
            bgColor = (vl == -1) ? bgColor : vl;
        }
        if(attr.size() > 2) {
            int vl = *(attr.begin() + 1);
            defaultColor = (vl == -1) ? defaultColor : vl;
        }
        if(attr.size() > 3) {
            int vl = *(attr.begin() + 1);
            defaultBgColor = (vl == -1) ? defaultBgColor : vl;
        }
    }
    this->setColor(bgColor, color);
    std::cout << msg << std::endl;
    this->setColor(defaultBgColor, defaultColor);
}

unsigned char WindowsIO::getChar() {
    unsigned char c = _getch();
    return c;
}

void WindowsIO::clearScreen() {
    if(system("CLS")) system("clear");
}