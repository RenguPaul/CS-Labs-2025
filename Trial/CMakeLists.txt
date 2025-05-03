cmake_minimum_required(VERSION 3.23)

set(project "Trial")

project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES
    Trial.cpp)

set(${project}_HEADERS
    Trial.h)

set(${project}_SOURCE_LIST
    ${${project}_SOURCES}
    ${${project}_HEADERS})

add_library(${project}
    STATIC
    ${${project}_SOURCE_LIST})

target_link_libraries(${project} PRIVATE Test)
target_compile_options(${project} PRIVATE -fPIC)
target_include_directories(${project} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Test)
