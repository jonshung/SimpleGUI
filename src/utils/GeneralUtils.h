#pragma once
#define _UTILITY_PACKAGE_
#include <cstdlib>
#include <sstream>
#include <string>
#include <fstream>
#include "Constant.h"

int getTextColor(int, int = Color::BLACK);

std::string concatenateString(std::initializer_list<std::string>);