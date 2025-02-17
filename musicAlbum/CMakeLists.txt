cmake_minimum_required(VERSION 3.23)

set(project "musicAlbum")
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES
        musicAlbum.cpp)
set(${project}_HEADERS
        musicAlbum.hpp)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/MusicAlbums.txt
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

set(${project}_SOURCE_LIST
        ${${project}_SOURCES}
        ${${project}_HEADERS})

add_library(${project}
        STATIC
        ${${project}_SOURCE_LIST})
