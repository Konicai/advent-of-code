cmake_minimum_required(VERSION 3.23)
project(adventofcode22 C)

set(CMAKE_C_STANDARD 99)

add_executable(adventofcode22 main.c day1/day1.c  day1/day1.h day2/day2.c day2/day2.h day3/day3.c day3/day3.h day4/day4.c day4/day4.h)
