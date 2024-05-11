cmake_minimum_required(VERSION 11)
project(lab_18 C)

set(CMAKE_C_STANDARD 99)

add_executable(op_lab_17 main.c
        libs/data_struct/string/string.h
        libs/data_struct/string/string.c
        libs/data_struct/lab18/lab18_solutions.h
        libs/data_struct/lab18/lab18_solutions.c)

add_subdirectory(libs)

target_link_libraries(data_struct)