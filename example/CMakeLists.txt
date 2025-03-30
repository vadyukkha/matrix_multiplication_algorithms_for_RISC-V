file(GLOB EXAMPLE_FILES "*.cpp")
add_executable(example_tests ${EXAMPLE_FILES})
target_link_libraries(example_tests api)
