cmake_minimum_required(VERSION 3.29)
project(KnightTour C)

set(CMAKE_C_STANDARD 11)

add_executable(KnightTour main.c
        knight.h)
