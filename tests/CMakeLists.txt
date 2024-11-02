# Downloading and configuring gtest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Creating  executable of api_tests and linking with gtest and our lab for matrix multiplication + api
file(GLOB API_TESTS_FILES "api_tests/*.cpp")
add_executable(api_tests ${API_TESTS_FILES})
target_link_libraries(api_tests api GTest::gtest_main)

# Creating  executable of kernel_tests and linking with gtest and our lab for matrix multiplication + api
file(GLOB KERNEL_TESTS_FILES "kernel_tests/*.cpp")
add_executable(kernel_tests ${KERNEL_TESTS_FILES})
target_link_libraries(kernel_tests api multiplication_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(kernel_tests)
gtest_discover_tests(api_tests)
