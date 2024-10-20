cmake_minimum_required(VERSION 3.14)
project(matrix_multiplication_risc_v)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Добавляем папку с хедерами
include_directories(${PROJECT_SOURCE_DIR}/include)

# Находим и компилируем нашу библотеку на С
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.c)
add_library(multiplication_lib ${SRC_FILES})
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)

# Создаем исполняемый файл для тестов
add_executable(
  matrix_multiplication_risc_v
  ${PROJECT_SOURCE_DIR}/tests/runtest.cpp
)

# Линкуемся с нашей библиотекой + gtest
target_link_libraries(
  matrix_multiplication_risc_v
  multiplication_lib
  GTest::gtest_main
)

# Добавляем тесты
enable_testing()
include(GoogleTest)
gtest_discover_tests(matrix_multiplication_risc_v)

