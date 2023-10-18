cmake_minimum_required(VERSION 3.0.0)
set (CMAKE_CXX_STANDARD 17)
project(SimpleGUI VERSION 0.1.0 LANGUAGES CXX)

SET(CURSES_USE_NCURSES TRUE)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Curses REQUIRED)

set (_SimpleGUIInclude "${CURSES_INCLUDE_DIRS}/ncurses" ${CURSES_INCLUDE_DIRS} "${CMAKE_CURRENT_LIST_DIR}" "${CMAKE_CURRENT_LIST_DIR}/libs" "${CMAKE_CURRENT_LIST_DIR}/utils" PARENT_SCOPE)

file (GLOB _MenuManagerSources "*.cpp")
file (GLOB _LibsSources "libs/*.cpp" "libs/*.hpp")
file (GLOB _UtilsSources "utils/*.cpp")
file (GLOB _ConfigSources "config/*.json")

set(_SimpleGUISources ${_MenuManagerSources} ${_LibsSources} ${_UtilsSources} PARENT_SCOPE)
set(_ConfigSources ${_ConfigSources} PARENT_SCOPE)