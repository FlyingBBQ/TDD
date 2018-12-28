##### simple CMake file #####
#
# --- MAIN CMAKE FILE ---
#
# CMake build project with static library and googletest

# Minimum version of CMake to use
cmake_minimum_required(VERSION 2.8.2 FATAL_ERROR)

# Name of the project
project(cbuf_gtest)

# set directory of the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

##### GoogleTest #####
# Download and unpack  googletest at configure time.
# configure_file() copies template file to build area,
# it also does variable substitution for CMAKE_BINARY_DIR.
# source: https://crascit.com/2015/07/25/cmake-gtest/
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)

# execute_process() executes the sub build of the CMakeLists we just copied.
# this forces CMake to fully build gtest instead of waiting untill build time.
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )

execute_process(COMMAND "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )

# prevent gtest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
                 "${CMAKE_BINARY_DIR}/googletest-build")

# The gtest/gmock targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if(CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include"
                        "${gmock_SOURCE_DIR}/include")
endif()

# Now simply link against gtest or gtest_main as needed. Eg
#add_executable(example example.cpp)
#target_link_libraries(example gtest_main)
#add_test(NAME example_test COMMAND example)

##### END GoogleTest #####

# Create main.cpp which uses gtest
file(WRITE src/main.cpp "#include \"gtest/gtest.h\"\n\n")
file(APPEND src/main.cpp "TEST(A, B) { SUCCEED(); }\n")
file(APPEND src/main.cpp "int main(int argc, char **argv) {\n")
file(APPEND src/main.cpp "  testing::InitGoogleTest(&argc, argv);\n")
file(APPEND src/main.cpp "  return RUN_ALL_TESTS();\n")
file(APPEND src/main.cpp "}\n")

# add subdirectories which contain their own CMakeLists
add_subdirectory(main/src)

# install command will place these files in DESTINATION
#install(TARGETS cbuf_gtest DESTINATION bin)
#install(FILES cbuf.h DESTINATION include)

