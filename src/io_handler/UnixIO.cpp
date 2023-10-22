#include "UnixIO.h"

UnixIO* _instance = nullptr;

UnixIO* UnixIO::instance() {
    if(_instance == nullptr) {
        _instance = new UnixIO();
        initscr();
    }
    return _instance;
}

UnixIO::~UnixIO() {
    endwin();
    delete this->_instance;
}

void UnixIO::print(std::string msg, std::initializer_list<int> attr) {
    // todo: color
    std::cout << msg;
}

unsigned char UnixIO::getChar() {
    noecho();
    cbreak();
    unsigned int c = getch();
    nocbreak();
    echo();
    return c;
}

void UnixIO::clearScreen() {
    clear();
}