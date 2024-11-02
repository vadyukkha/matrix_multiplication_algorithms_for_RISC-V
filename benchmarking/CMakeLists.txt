file(GLOB BENCHMARK_FILES "*.c")
add_executable(benchmark ${BENCHMARK_FILES})
target_link_libraries(benchmark multiplication_lib)