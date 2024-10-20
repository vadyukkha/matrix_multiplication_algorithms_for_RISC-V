cmake_minimum_required(VERSION 3.14)
project(matrix_multiplication_risc_v)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include directories adding
include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/API)

# our library for matrix multiplication adding (API + C algorithms realization)
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.c ${PROJECT_SOURCE_DIR}/API/*.cpp)
add_library(multiplication_lib ${SRC_FILES})

# flag to enable/disable tests compilation
option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()