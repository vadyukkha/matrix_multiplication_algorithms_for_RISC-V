# Downloading and configuring gtest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Creating  executable of tests and linking with gtest and our lab for matrix multiplication + api
file(GLOB TESTS_FILES "*.cpp")
add_executable(tests ${TESTS_FILES})
target_link_libraries(tests api multiplication_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)
