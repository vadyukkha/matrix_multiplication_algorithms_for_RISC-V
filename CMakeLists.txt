cmake_minimum_required(VERSION 3.14)
project(matrix_multiplication_risc_v LANGUAGES C CXX ASM)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# CMP0135 policy should be new
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

# C lib and api lib source files
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*)
file(GLOB API_FILES ${PROJECT_SOURCE_DIR}/api/*.cpp)

# C lib adding
add_library(multiplication_lib ${SRC_FILES})
target_include_directories(multiplication_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)

# api lib adding
add_library(api ${API_FILES})
target_include_directories(api PUBLIC ${PROJECT_SOURCE_DIR}/api)

# C lib and api linking
target_link_libraries(api PRIVATE multiplication_lib)

# flag to enable/disable tests compilation
option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

# flag to enable/disable benchmark compilation
option(BUILD_BENCHMARK "Build benchmark files" ON)
if (BUILD_BENCHMARK) 
  add_subdirectory(benchmarking)
endif()
