cmake_minimum_required(VERSION 3.23)

set(project "lab_6")
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES
        main.cpp)

add_subdirectory(MyVector)
add_subdirectory(Term)
add_subdirectory(Polynomial)

set(${project}_SOURCE_LIST
        ${${project}_SOURCES})

add_executable(${project}
        ${${project}_SOURCE_LIST})

target_link_libraries(${project} MyVector)
target_link_libraries(${project} Term)
target_link_libraries(${project} Polynomial)
