###############################################################################
# --- MAIN CMAKE FILE ---
#
# Author: FlyingBBQ 2018
# About:  CMake build project with static library and googletest
###############################################################################

# Minimum version of CMake to use
cmake_minimum_required(VERSION 2.8.2 FATAL_ERROR)

###############################################################################
#   Options
###############################################################################
# Turn on with 'cmake -Dmyvarname=ON'.
# Makes boolean 'test' available.
# source: https://github.com/dmonopoly/gtest-cmake-example/blob/master/CMakeLists.txt
option(test "Build all tests." OFF)
option(get_gtest "Get and build GoogleTest." OFF)
option(gen_test_main "Generate test main.cpp." OFF)

###############################################################################
#   Configuration
###############################################################################
# Name of the project
set(PROJECT_NAME cbuf)
project(${PROJECT_NAME})

# name of the test executable
set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)

# set directory of the executable and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

###############################################################################
#   BEGIN GoogleTest
###############################################################################
# use boolean with compile option to build and make GoogleTest
if(gen_gtest)
    # Download and unpack  googletest at configure time.
    # configure_file() copies template file to build area,
    # it also does variable substitution for CMAKE_BINARY_DIR.
    # source: https://crascit.com/2015/07/25/cmake-gtest/
    configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)

    # execute_process() executes the sub build of the CMakeLists we just copied.
    # this forces CMake to fully build gtest instead of waiting untill build time.
    # use RESULT_VARIABLE for error handling

    # CMake gtest
    execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/googletest-download" )
    # error handling
    if(result)
        message(FATAL_ERROR "CMake step for googletest failed: ${result}")
    endif()

    # build gtest
    execute_process(COMMAND "${CMAKE_COMMAND}" --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/googletest-download" )
    if(result)
        message(FATAL_ERROR "Build step for googletest failed: ${result}")
    endif()

    # prevent gtest from overriding our compiler/linker options
    # when building with Visual Studio
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    # Add googletest directly to our build. This adds
    # the following targets: gtest, gtest_main, gmock
    # and gmock_main
    add_subdirectory("${CMAKE_CURRENT_BINARY_DIR}/googletest-src"
        "${CMAKE_CURRENT_BINARY_DIR}/googletest-build")

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
endif()
###############################################################################
#   END GoogleTest
###############################################################################

# Create main.cpp which uses gtest
if(gen_test_main)
    file(WRITE  test/main.cpp "#include \"gtest/gtest.h\"\n\n")
    file(APPEND test/main.cpp "TEST(A, B) { SUCCEED(); }\n")
    file(APPEND test/main.cpp "int main(int argc, char **argv) {\n")
    file(APPEND test/main.cpp "  testing::InitGoogleTest(&argc, argv);\n")
    file(APPEND test/main.cpp "  return RUN_ALL_TESTS();\n")
    file(APPEND test/main.cpp "}\n")
endif()

###############################################################################
#   Libraries and executables
###############################################################################
# Add subdirectories which contain their own CMakeLists.
# These subdirs will recursivly build and link, keeping the main file clean.
# source: https://youyue123.github.io/tech/2018/01/29/TDD-for-C++-in-CMake-And-GoogleTest.html
add_subdirectory(main)

###############################################################################
#   Testing
###############################################################################
if(test)
    # link and test
    #add_subdirectory(test)
endif()

###############################################################################
#   Installing
###############################################################################
# install command will place these files in DESTINATION
#install(TARGETS cbuf_gtest DESTINATION bin)
#install(FILES cbuf.h DESTINATION include)
