cmake_minimum_required(VERSION 3.23)

set(project "Test")

project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES
    Test.cpp)

set(${project}_HEADERS
    Test.h)

set(${project}_SOURCE_LIST
    ${${project}_SOURCES}
    ${${project}_HEADERS})

add_library(${project}
    STATIC
    ${${project}_SOURCE_LIST})

target_compile_options(${project} PRIVATE -fPIC)
target_include_directories(${project} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
