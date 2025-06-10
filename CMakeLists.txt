# @file
# @author Erwin Meza Vega <emezav@unicauca.edu.co>, <emezav@gmail.com>
# @copyright MIT License
# Configuration file for CMake.

# Minimum required version: 3.24
cmake_minimum_required(VERSION 3.24)

# Get current directory name and replace spaces with underscores.
cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME ProjectName)
string(REPLACE " " "_" ProjectId ${ProjectName})

# Use current directory as project name (Visual Studio solution name)
project(${ProjectName}
  VERSION 1.0
  LANGUAGES CXX)

# To use a custom project name:
# comment the project(...) line before this comment,
# replace MYPROJECT with the desired project name and uncomment the following line:
#project("MYPROJECT")

# Set position independent code to ON, required for some libraries
# Please check carefully for each library required on the project
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Use folders to group CMake targets
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Add global include directory "./include"
include_directories(${CMAKE_SOURCE_DIR}/include)

# Set C++ to std 17
# UNCOMMENT THIS IF YOU INTEND TO SET c++17 FOR YOUR PROJECT ONLY
#set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Begin project executable section
# Uncomment this section if you want to create project executable

# Add c/c++ headers and sources
# UNCOMMENT THIS IF YOU INTEND TO HAVE TOUR OWN main.cpp
#file(GLOB project_sources "${CMAKE_SOURCE_DIR}/src/*.cpp" "${CMAKE_SOURCE_DIR}/include/*.h")

# Add executable to the project
# UNCOMMENT THIS IF YOU INTEND TO HAVE TOUR OWN main.cpp
#add_executable (${PROJECT_NAME} ${project_sources})

# Set default start project
#set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# Set link flags to mirror project link flags
# UNCOMMENT THIS IF YOU INTEND TO HAVE TOUR OWN main.cpp
#set_property(TARGET ${PROJECT_NAME} PROPERTY LINK_FLAGS ${PROJ_LINK_FLAGS})

# Set debugger working directory to source dir
# UNCOMMENT THIS IF YOU INTEND TO HAVE TOUR OWN main.cpp
#set_property(TARGET ${PROJECT_NAME} PROPERTY DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# Set debugger working directory to source dir (for Visual Studio)
# UNCOMMENT THIS IF YOU INTEND TO HAVE TOUR OWN main.cpp
#set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# End project executable section

# Begin examples section

# Add example executables
file(GLOB EXAMPLES "examples/*.cpp")

# Iterate over all .cpp files under the examples/ folder
foreach(example ${EXAMPLES})
  # Get the filename without the extension
  get_filename_component(executable_name ${example} NAME_WE)
  # Add example executable
  add_executable(${executable_name} ${example})
endforeach()

# End project examples section

# Begin project tests section

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add c/c++ headers and sources
file(GLOB test_sources "${CMAKE_SOURCE_DIR}/test/*.cc" "${CMAKE_SOURCE_DIR}/include/*.h")

# Enable tests
enable_testing()

# Create test project
set(TEST_PROJECT "${PROJECT_NAME}_test")

# Create an interface library for the header-only library
add_library(${PROJECT_NAME} INTERFACE)

# Set include directories for the interface library
target_include_directories(${PROJECT_NAME} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

# Add test project executable
add_executable(
  ${TEST_PROJECT}
  ${test_sources}
)

# Add gtest_main library for test project
target_link_libraries(
  ${TEST_PROJECT}
  GTest::gtest_main
)

# Include google test framework
include(GoogleTest)

# Discover tests!
gtest_discover_tests(${TEST_PROJECT})

# End project tests section

# Install target for this library
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}-targets)
install(DIRECTORY include/ DESTINATION include)
install(EXPORT ${PROJECT_NAME}-targets DESTINATION lib/cmake/${PROJECT_NAME})



