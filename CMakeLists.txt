cmake_minimum_required(VERSION 3.22.1)

project(comp-math-systems-of-linear-equations)

set(CMAKE_CXX_STANDARD "17")
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_BUILD_TYPE "sanitized")
set(CXX_COMMON_FLAGS "-std=c++${CMAKE_CXX_STANDARD} -stdlib=libc++ -Wall -Werror")

set(CMAKE_EXPORT_COMPILE_COMMANDS "true")

if (CMAKE_BUILD_TYPE STREQUAL "sanitized")
    set(
        CMAKE_CXX_FLAGS 
        "${CXX_COMMON_FLAGS} -g -fsanitize=address,undefined,leak"
    )
elseif (CMAKE_BUILD_TYPE STREQUAL "release")
    set(
        CMAKE_CXX_FLAGS 
        "${CXX_COMMON_FLAGS} -O3"
    )
elseif (CMAKE_BUILD_TYPE STREQUAL "debug")
    set(
        CMAKE_CXX_FLAGS 
        "${CXX_COMMON_FLAGS} -g"
    )
endif ()

include_directories("src")
add_executable(
	app
	src/main.cpp
    src/math/linal/matrix.h
    src/math/sle/method/iteration/valid-sle.h
    src/math/sle/method/iteration/solution.h
)

