cmake_minimum_required(VERSION 3.0.0)
set (CMAKE_CXX_STANDARD 17)

# Set this to your project name
set(_BuildProject "VendingMachine")
# Optional: change this if you want to specify the name of the outputting executable
set(_OutExecutable ${_BuildProject})

project(_BuildProject VERSION 0.1.0 LANGUAGES CXX)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # require at least gcc 4.8
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.8)
        message(FATAL_ERROR "GCC version must be at least 4.8!")
    endif()
endif()

if(WIN32)
    if(CMAKE_SYSTEM_VERSION VERSION_LESS 10)
        message(FATAL_ERROR "Windows version must be atleast 10")
    endif()
endif()

add_subdirectory(src)
set(_ProjectBuildPaths "${_BuildProject}/main.cpp"
                       "${_BuildProject}/UserOrderHandler.cpp"
                       "${_BuildProject}/VendingMachine.cpp"
    )

add_executable (BuildingTarget ${_ProjectBuildPaths})
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/out")
set_target_properties(BuildingTarget PROPERTIES OUTPUT_NAME ${_OutExecutable})

target_include_directories(BuildingTarget PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/VendingMachine")
target_link_libraries(BuildingTarget SimpleGUI)

# Change this to your project config path to automatically load it to the build path
set(_ConfigPath "${CMAKE_SOURCE_DIR}/${_BuildProject}/locale")
add_custom_command(TARGET BuildingTarget POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${_ConfigPath} $<TARGET_FILE_DIR:BuildingTarget>/locale)