cmake_minimum_required(VERSION 3.0.0)
set (CMAKE_CXX_STANDARD 17)
project(SimpleGUI VERSION 0.1.0 LANGUAGES C CXX)

set (CMAKE_CXX_FLAGS "-I ${CMAKE_SOURCE_DIR}")

file (GLOB _VendingMachineSources "VendingMachine/*.cpp")
file (GLOB _MenuManagerSources  "src/*.cpp")
file (GLOB _LibsSources "src/libs/*.cpp")
file (GLOB _UtilsSources "src/utils/*.cpp")
add_executable (VendingMachine ${_VendingMachineSources} ${_MenuManagerSources} ${_LibsSources} ${_UtilsSources})