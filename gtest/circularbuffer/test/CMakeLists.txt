###############################################################################
# --- SUB CMAKE FILE ---
###############################################################################
add_executable(example_test cbuf_test.cpp)

target_include_directories(example_test PRIVATE ${PROJECT_SOURCE_DIR}/main/include)

target_link_libraries(example_test cbuf_base gtest_main)

add_test(NAME example COMMAND example_test)
