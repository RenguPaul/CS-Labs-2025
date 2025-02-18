cmake_minimum_required(VERSION 3.23)

set(project "lab_2")
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES
        main1.cpp)

add_subdirectory(musicAlbum)
add_subdirectory(musicAlbum/musicAlbum)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/musicAlbums.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

set(${project}_SOURCE_LIST
        ${${project}_SOURCES})

add_executable(${project}
        ${${project}_SOURCE_LIST})
