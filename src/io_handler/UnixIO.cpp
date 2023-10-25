#include "UnixIO.h"

UnixIO* UnixIO::instance() {
    if (_instance == nullptr) {
        _instance = new UnixIO();
    }
    return _instance;
}

UnixIO::~UnixIO() {
    delete this->_instance;
}

void UnixIO::noEcho() {
    _term.c_lflag &= ~ECHO;
    _term.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &_term);
}

void UnixIO::echo() {
    _term.c_lflag |= ECHO;
    _term.c_lflag |= ICANON;
    tcsetattr(0, TCSANOW, &_term);
}

UnixIO::UnixIO() {
    tcgetattr(0, &_term);
}

void UnixIO::print(std::string msg, std::initializer_list<std::string> attr) {
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

int UnixIO::getChar() {
    noEcho();
    int c = getchar();
    echo();
    return keyTranslate(c);
}

int UnixIO::keyTranslate(int c) {
    if (c == 27) {
        int cx = getChar();
        if (cx == '[') {
            return keyTranslate(c);
        }
        else {
            return Keys::ESC;
        }
    }
    switch (c) {
    case UnixKeys::Up: {
        return Keys::UP;
    }
    case UnixKeys::Down: {
        return Keys::DOWN;
    }
    case UnixKeys::Left: {
        return Keys::LEFT;
    }
    case UnixKeys::Right: {
        return Keys::RIGHT;
    }
    case UnixKeys::Enter: {
        return Keys::ENTER;
    }
    default: {
        return 3;
    }
    }
}

void UnixIO::clearScreen() {
    system("clear");
}