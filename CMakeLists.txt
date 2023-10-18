cmake_minimum_required(VERSION 3.0.0)
set (CMAKE_CXX_STANDARD 17)

# Set this to your project name
set(_BuildProject "VendingMachine")
# Optional: change this if you want to specify the name of the outputting executable
set(_OutExecutable ${_BuildProject})

project(_BuildProject VERSION 0.1.0 LANGUAGES CXX)

add_subdirectory(src)
include_directories((${_SimpleGUIInclude}))
file (GLOB _BuildSources "${_BuildProject}/*.cpp" "${_BuildProject}/*.h")

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/out")
add_executable (BuildingTarget ${_SimpleGUISources} ${_BuildSources})
set_target_properties(BuildingTarget PROPERTIES OUTPUT_NAME ${_OutExecutable})
target_include_directories(BuildingTarget PRIVATE ${_SimpleGUIInclude})

# Change this to your project config path to automatically load it to the build path
set(_ConfigPath "${CMAKE_SOURCE_DIR}/src/config/")
add_custom_command(TARGET BuildingTarget POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${_ConfigPath} $<TARGET_FILE_DIR:BuildingTarget>/config)