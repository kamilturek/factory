cmake_minimum_required(VERSION 3.15)

project(factory CXX)

# Compiler warnings
add_library(warnings INTERFACE)
include(cmake/CompilerWarnings.cmake)
set_project_warnings(warnings)

# Sanitizers
add_library(sanitizers INTERFACE)
include(cmake/Sanitizers.cmake)
enable_sanitizers(sanitizers)

# Compile command database for clang-tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(factory src/main.cpp)
target_link_libraries(factory PRIVATE warnings sanitizers)
target_compile_features(factory PRIVATE cxx_std_17)
