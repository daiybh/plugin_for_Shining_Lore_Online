# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

project ("OP_findPIC")

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

set(CMAKE_CXX_STANDARD 17)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    MESSAGE(STATUS "----------------Now is MSVC EHA----------------")
    set(CMAKE_CXX_FLAGS_RELEASE "/MT /O2 /EHa")
    set(CMAKE_C_FLAGS_RELEASE "/MT  /O2 /EHa")
    set(CMAKE_CXX_FLAGS_DEBUG "/MT /Zi /EHa")
    set(CMAKE_C_FLAGS_DEBUG "/MT /Zi /EHa")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MT /O2  /EHa")
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "/MT /O2 /EHa")
endif()

# 包含子项目。
add_subdirectory ("src")
