cmake_minimum_required(VERSION 3.14)
project(interpreter)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O1")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE LIBRARY_SOURCES "src/*.cpp")
add_library(interpreter_lib ${LIBRARY_SOURCES})

add_executable(
  interpreter
  main.cpp
)

target_link_libraries(
    interpreter
    interpreter_lib
)

enable_testing()

file(GLOB TEST_SOURCES "tests/*.cpp")
foreach(test_source ${TEST_SOURCES})
    get_filename_component(test_name ${test_source} NAME_WE)
    add_executable(${test_name} ${test_source})
    target_link_libraries(${test_name} PRIVATE gtest_main)
    target_link_libraries(${test_name} PRIVATE interpreter_lib)
    # Optionally, link other libraries that your tests depend on
    # target_link_libraries(${test_name} PRIVATE <your_libraries_here>)
endforeach()

include(GoogleTest)
# gtest_discover_tests(hello_test)
