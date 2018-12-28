###############################################################################
# --- SUB CMAKE FILE ---
###############################################################################
# add another level of subdirectories which also contain CMakeLists.txt
add_subdirectory(src)
add_subdirectory(sample_lib)

# create executable with NAME from FILES
add_executable(${PROJECT_NAME} main.c)

# link libraries to executable.
# library generation is done is subdirectories
target_link_libraries(${PROJECT_NAME} cbuf_base sample_lib)
