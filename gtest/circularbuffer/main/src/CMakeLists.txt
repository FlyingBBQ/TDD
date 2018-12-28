# include header files
include_directories(${PROJECT_SOURCE_DIR}/main/inc/)

# manually add src files to variable
set(main_src_files
    cbuf.c
)

# use wildcard to add variables
#file(GLOB main_src_files
#    "*.c"
#)

# create executable with NAME from FILES
add_executable(cbuf_gtest cbuf.c)

