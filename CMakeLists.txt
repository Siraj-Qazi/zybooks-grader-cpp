cmake_minimum_required(VERSION 3.15)
project(grader C)

set(CMAKE_C_STANDARD 11)

add_executable(grader main.c functions.c)