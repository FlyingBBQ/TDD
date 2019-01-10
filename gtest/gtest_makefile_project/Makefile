###############################################################################
# Makefile for building googletest libraries and
# linking them to multiple tests
#
# Author: Derek Cardol
###############################################################################

# Name of the test executable
TEST = example_test

# Directories
###############################################################################
# location of googletest files
GTEST_DIR = gtest

# Points to the location of the googletest libraries and source files
GTEST_LIB_DIR = $(GTEST_DIR)/lib
GTEST_SRC_DIR = $(GTEST_DIR)/src

# All googletest headers
GTEST_HEADERS = $(GTEST_DIR)/inc

# Where to find user code.
SRC_DIR = mock/src
INC_DIR = mock/inc

# Where to find tests
TEST_DIR = tests

# Build directory for objects and executables
BUILD_DIR = Debug
OBJ_SRC_DIR = $(BUILD_DIR)/src
OBJ_TEST_DIR = $(BUILD_DIR)/tests

# Source and header files
###############################################################################
# Use wildcard to automatically include all sources
INC_HEADERS := $(wildcard $(INC_DIR)/*.h)

# Compile the source files to object files
# first gather all sources with a wildcard
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
# Take the names from all %.cpp files and compile the into object files %.o
SRC_OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_SRC_DIR)/%.o,$(SRC_FILES))

# Compile the test sources to object files
TEST_FILES := $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJECTS := $(patsubst $(TEST_DIR)/%.cpp,$(OBJ_TEST_DIR)/%.o,$(TEST_FILES))

# Compiler settings
###############################################################################
# Compiler
CXX = g++

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_HEADERS)

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -pthread -std=c++11

# Make options
###############################################################################
# "make"
# Running "make" defaults to "make all", which generates the libs and tests
all : lib tests

# "make lib"
# Generate the libraries
lib : build $(GTEST_LIB_DIR)/libgtest.a $(GTEST_LIB_DIR)/libgtest_main.a

# "make build"
# Make the output directories where all the generated files will be placed
build :
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(OBJ_SRC_DIR)
	@mkdir -p $(OBJ_TEST_DIR)

# "make tests"
# Just make the tests
tests : $(TEST)

# "make run"
# Run the generated test executable
run : tests
	./$(TEST)

# "make clean"
# Remove the build directory
clean :
	rm -rf $(BUILD_DIR)
	rm $(TEST)

# "make cleanlib"
# Remove the generated googletest libraries
cleanlib :
	rm $(GTEST_LIB_DIR)/*

# Compiling the static googletest libraries
###############################################################################
# Compile the source files into object files
$(BUILD_DIR)/gtest-all.o : $(GTEST_DIR)/src/gtest-all.cpp $(GTEST_DIR)/inc/gtest.h
	@echo "Compiling gtest-all.o"
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) \
	-c $(GTEST_DIR)/src/gtest-all.cpp -o $@
	@echo " "

$(BUILD_DIR)/gtest_main.o : $(GTEST_DIR)/src/gtest_main.cpp $(GTEST_DIR)/inc/gtest.h
	@echo "Compiling gtest_main.o"
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) \
	-c $(GTEST_DIR)/src/gtest_main.cpp -o $@
	@echo " "

# Link the object files into static libraries
$(GTEST_LIB_DIR)/libgtest.a : $(BUILD_DIR)/gtest-all.o
	@echo "Linking libgtest.a"
	$(AR) $(ARFLAGS) $@ $^
	@echo " "

$(GTEST_LIB_DIR)/libgtest_main.a : $(BUILD_DIR)/gtest-all.o $(BUILD_DIR)/gtest_main.o
	@echo "Linking libgtest_main.a"
	$(AR) $(ARFLAGS) $@ $^
	@echo " "

# Compile the source files to object files
###############################################################################
$(OBJ_SRC_DIR)/%.o : $(SRC_DIR)/%.cpp $(INC_HEADERS) $(GTEST_HEADERS)
	@echo "Building source objects..."
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@
	@echo " "

# compile the test files to object files
$(OBJ_TEST_DIR)/%.o : $(TEST_DIR)/%.cpp $(INC_HEADERS) $(GTEST_HEADERS)
	@echo "Building test objects..."
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@
	@echo " "

# Create the executable by linking all the objects together
###############################################################################
$(TEST) : $(SRC_OBJECTS) $(TEST_OBJECTS) $(GTEST_LIB_DIR)/libgtest_main.a
	@echo "Generating executable..."
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -L$(GTEST_LIB_DIR) -lgtest_main -lpthread $^ -o $@
	@echo " "
	@echo "Success!"
