cmake_minimum_required(VERSION 3.15)

project(factory CXX)

# Build type
include(cmake/BuildType.cmake)

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

# ncurses
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# threads
find_package(Threads REQUIRED)

include_directories(include)
include_directories(include/UI)

add_executable(
  factory
  src/main.cpp
  src/CountingLock.cpp
  src/Factory.cpp
  src/DoubleMachine.cpp
  src/UI/UI.cpp
  src/UI/Figure.cpp
  src/UI/DoubleMachineFigure.cpp
  src/UI/SingleMachineFigure.cpp
  src/UI/HalfMachineFigure.cpp
  src/UI/CarFigure.cpp)
target_link_libraries(factory PRIVATE warnings sanitizers ${CURSES_LIBRARIES}
                                      ${CMAKE_THREAD_LIBS_INIT})
target_compile_features(factory PRIVATE cxx_std_17)
