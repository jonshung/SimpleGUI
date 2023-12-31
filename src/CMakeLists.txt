cmake_minimum_required(VERSION 3.10.0)
set (CMAKE_CXX_STANDARD 17)
project(SimpleGUI VERSION 0.1.0 LANGUAGES CXX)

set (_SimpleGUIInclude  "${CMAKE_CURRENT_SOURCE_DIR}/" "${CMAKE_CURRENT_SOURCE_DIR}/libs"
                        "${CMAKE_CURRENT_SOURCE_DIR}/utils" "${CMAKE_CURRENT_SOURCE_DIR}/io_handler"
                        "${CMAKE_CURRENT_SOURCE_DIR}/eventhandler"
                        )

file (GLOB _MenuManagerSources "*.cpp")
file (GLOB _LibsSources "libs/*.cpp" "libs/*.hpp")
file (GLOB _UtilsSources "utils/*.cpp")
file (GLOB _ConfigSources "config/*.json")
file (GLOB _IOSources "io_handler/*.cpp")
file (GLOB _EventHandlerSources "eventhandler/*.cpp")

if(WIN32)
    list(FILTER _IOSources EXCLUDE REGEX ".*UnixIO\\.cpp$")
elseif(UNIX)
    list(FILTER _IOSources EXCLUDE REGEX ".*WindowsIO\\.cpp$")
endif()

set(_SimpleGUISources ${_MenuManagerSources} ${_LibsSources} ${_UtilsSources} ${_IOSources} ${_EventHandlerSources})
set(_ConfigSources ${_ConfigSources} PARENT_SCOPE)

set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/out")
add_library(SimpleGUI SHARED ${_SimpleGUISources})
target_include_directories(SimpleGUI PUBLIC ${_SimpleGUIInclude})