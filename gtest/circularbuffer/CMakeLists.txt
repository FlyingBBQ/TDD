# simple CMake file

# Minimum version of CMake to use
cmake_minimum_required(VERSION 2.8.2)

# Name of the project
project(cbuf_gtest)

# set directory of the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# add subdirectories which contain their own CMakeLists
add_subdirectory(main/src)

# install command will place these files in DESTINATION
#install(TARGETS cbuf_gtest DESTINATION bin)
#install(FILES cbuf.h DESTINATION include)
