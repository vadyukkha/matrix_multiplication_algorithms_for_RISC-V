# benchmarking library
file(GLOB BENCHMARK_FILES "benchmarking.c")
add_library(BENCHMARK_LIB STATIC ${BENCHMARK_FILES})

# benchmarking tests
file(GLOB BENCHMARK_TEST_FILES "benchmarking_naive.c")
add_executable(benchmark ${BENCHMARK_TEST_FILES})
target_link_libraries(benchmark PRIVATE multiplication_lib BENCHMARK_LIB)
