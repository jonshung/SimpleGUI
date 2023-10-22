cmake_minimum_required(VERSION 3.0.0)
set (CMAKE_CXX_STANDARD 17)
project(SimpleGUI VERSION 0.1.0 LANGUAGES CXX)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CURSES_USE_NCURSES TRUE)
find_package(Curses REQUIRED)

set (_SimpleGUIInclude  "${CMAKE_CURRENT_LIST_DIR}" "${CMAKE_CURRENT_LIST_DIR}/libs" 
                        "${CMAKE_CURRENT_LIST_DIR}/utils" "${CMAKE_CURRENT_LIST_DIR}/io_handler"
                        )

file (GLOB _MenuManagerSources "*.cpp")
file (GLOB _LibsSources "libs/*.cpp" "libs/*.hpp")
file (GLOB _UtilsSources "utils/*.cpp")
file (GLOB _ConfigSources "config/*.json")
file (GLOB _IOSources "io_handler/*.cpp")

if(WIN32)
    list(FILTER _IOSources EXCLUDE REGEX ".*UnixIO\\.cpp$")
elseif(UNIX)
    list(FILTER _IOSources EXCLUDE REGEX ".*WindowsIO\\.cpp$")
endif()

message("${_IOSources}")

set(_SimpleGUISources ${_MenuManagerSources} ${_LibsSources} ${_UtilsSources} ${_IOSources})
set(_ConfigSources ${_ConfigSources} PARENT_SCOPE)

add_library(SimpleGUI ${_SimpleGUISources})
target_include_directories(SimpleGUI PUBLIC ${_SimpleGUIInclude})