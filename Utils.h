#pragma once
#define _UTILITY_PACKAGE_
#include <cstdlib>
#include <sstream>
#include <string>

enum Color {
    BLACK = 0,
    NAVY = 1,
    GREEN = 2,
    BLUE = 3,
    DARK_RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    GRAYLY = 7,
    GRAY = 8,
    SKY_BLUE = 9,
    LIME = 10,
    AQUA = 11,
    RED = 12,
    PINK = 13,
    PALE_YELLOW = 14,
    WHITE = 15
};
enum Keys : int {
    Arrow = 224,
    Up = 72,
    Down = 80,
    Left = 75,
    Right = 77,
    EscapeKey = 27,
    Enter = 13,
    Del = 83
};

int getTextColor(int colorId, int backgroundColor = Color::BLACK);
void clearScreen();

std::string concatenateString(std::initializer_list<std::string> list);