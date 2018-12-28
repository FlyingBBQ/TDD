###############################################################################
# --- SUB CMAKE FILE ---
###############################################################################
# this is a minimal example how to add a library
# https://stackoverflow.com/questions/46296487/include-headers-with-a-library-in-cmake
add_library(sample_lib STATIC cbuf_lib.c)

# include the header files as PUBLIC so other targets can see them
target_sources(sample_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/cbuf_lib.h)

# include the current directory since all the files are located here.
# make the library as interface
target_include_directories(sample_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
