###############################################################################
# --- SUB CMAKE FILE ---
###############################################################################
# manually add src files to variable
set(cbuf_srcs
    cbuf.c
)

# set include directory
set(cbuf_include_dir ${PROJECT_SOURCE_DIR}/main/include)

# make sure to add the header files if using target_include_directories()
# https://stackoverflow.com/questions/13703647/how-to-properly-add-include-directories-with-cmake
set(cbuf_incs
    ${cbuf_include_dir}/cbuf.h
)

# use wildcard to add variables
#file(GLOB src_files
#    "*.c"
#    "*.h"
#)

# Declare the library
add_library(cbuf_base STATIC
    ${cbuf_incs}
    ${cbuf_srcs}
)

# Specify here the include directories exported by this library.
# Use target_include_directories() over include_directories() because it
# allows to append a directory for a specific project/target without (maybe)
# unnecessary inheritance or clashing of various include directories.
# The directory should be the include directory.
target_include_directories(cbuf_base PUBLIC
    ${cbuf_include_dir}
)
