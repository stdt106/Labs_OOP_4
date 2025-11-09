cmake_minimum_required(VERSION 3.20)
project(Labs_OOP_4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/std:c++latest)
else()
    add_compile_options(-std=c++20)
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
)

FetchContent_MakeAvailable(googletest)

add_executable(run_file
    src/main.cpp
)

target_include_directories(run_file PRIVATE include)
target_compile_features(run_file PRIVATE cxx_std_20)

add_executable(tests 
    tests/tests.cpp
)

target_include_directories(tests PRIVATE include)
target_compile_features(tests PRIVATE cxx_std_20)
target_link_libraries(tests PRIVATE GTest::gtest_main)

enable_testing()
add_test(NAME MyProjectTests COMMAND tests)