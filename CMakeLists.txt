cmake_minimum_required(VERSION 3.0.0)
set (CMAKE_CXX_STANDARD 17)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # require at least gcc 4.8
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.8)
        message(FATAL_ERROR "GCC version must be at least 4.8!")
    endif()
endif()

# Set this to your project name
set(_BuildProject "VendingMachine")
# Optional: change this if you want to specify the name of the outputting executable
set(_OutExecutable ${_BuildProject})

project(_BuildProject VERSION 0.1.0 LANGUAGES CXX)

SET(CURSES_USE_NCURSES TRUE)
find_package(Curses REQUIRED)
add_subdirectory(src)

set (_IncludePaths "${CMAKE_SOURCE_DIR}/src" "${CMAKE_SOURCE_DIR}/src/libs" 
                    "${CMAKE_SOURCE_DIR}/src/utils" "${CMAKE_SOURCE_DIR}/src/io_handler" "${CMAKE_SOURCE_DIR}/VendingMachine")

set(_ProjectBuildPaths "${_BuildProject}/*.cpp" "${_BuildProject}/*.h")
file (GLOB _BuildSources ${_ProjectBuildPaths})

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/out")
add_executable (BuildingTarget ${_BuildSources})

target_include_directories(BuildingTarget PUBLIC ${_IncludePaths} ${CURSES_INCLUDE_DIRS} "${CURSES_INCLUDE_DIRS}/ncurses")

target_link_libraries(BuildingTarget ${CURSES_LIBRARIES} SimpleGUI)
set_target_properties(BuildingTarget PROPERTIES OUTPUT_NAME ${_OutExecutable})

# Change this to your project config path to automatically load it to the build path
set(_ConfigPath "${CMAKE_SOURCE_DIR}/src/config")
add_custom_command(TARGET BuildingTarget POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${_ConfigPath} $<TARGET_FILE_DIR:BuildingTarget>/config)