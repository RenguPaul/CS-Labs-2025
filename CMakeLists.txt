cmake_minimum_required(VERSION 3.23)

set(project "lab_7")
project(${project})

set(CMAKE_CXX_STANDARD 17)


add_executable(${project} main.cpp)

add_subdirectory(MyVector)
add_subdirectory(MySet)
add_subdirectory(Test)
add_subdirectory(Exam)
add_subdirectory(FinalExam)
add_subdirectory(Trial)

target_link_libraries(${project}
    MyVector
    MySet
    Trial
    FinalExam
    Exam
    Test
)
