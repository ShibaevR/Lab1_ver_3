cmake_minimum_required(VERSION 3.17)
project(lab1_retry C)

set(CMAKE_C_STANDARD 99)

add_executable(lab1_retry main.c matrix.c matrix.h tests.c tests.h fieldinfo.h int-element.c int-element.h float-element.c float-element.h)