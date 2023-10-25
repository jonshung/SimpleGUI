#include "WindowsIO.h"

// initialize instance pointer
WindowsIO* WindowsIO::_instance = nullptr;

WindowsIO::WindowsIO() {
    _WindowsHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleMode(_WindowsHandle, ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
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

void WindowsIO::print(std::string msg, std::initializer_list<std::string> attr) {
    std::string bgColor = "\033[48;5;0m";
    std::string color = "\033[38;5;15m";
    std::string defaultBgColor = "\033[48;5;0m";
    std::string defaultColor = "\033[38;5;15m";

    if (attr.size() > 0) {
        color = *(attr.begin());
        color = "\033[38;5;" + color + "m";
        if (attr.size() > 1) {
            std::string vl = *(attr.begin() + 1);
            bgColor = (vl == "") ? bgColor : ("\033[48;5;" + vl + "m");
        }
        if (attr.size() > 2) {
            std::string vl = *(attr.begin() + 1);
            defaultColor = (vl == "") ? defaultColor : ("\033[38;5;" + vl + "m");
        }
        if (attr.size() > 3) {
            std::string vl = *(attr.begin() + 1);
            defaultBgColor = (vl == "") ? defaultBgColor : ("\033[48;5;" + vl + "m");
        }
    }

    std::cout << color << bgColor << msg << "\033[0m" << std::endl;
}

int WindowsIO::getChar() {
    int c = _getch();
    return keyTranslate(c);
}

int WindowsIO::keyTranslate(int c) {
    if(c == WindowsKeys::Numpad || c == WindowsKeys::Arrow) {
        return keyTranslate(_getch());
    }

    switch(c) {
        case WindowsKeys::Up: {
            return Keys::UP;
        }
        case WindowsKeys::Down: {
            return Keys::DOWN;
        }
        case WindowsKeys::Left: {
            return Keys::LEFT;
        }
        case WindowsKeys::Right: {
            return Keys::RIGHT;
        }
        case WindowsKeys::Enter: {
            return Keys::ENTER;
        }
        default: {
            return 3;
        }
    }
}

void WindowsIO::clearScreen() {
    if(system("CLS")) system("clear");
}