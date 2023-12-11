cmake_minimum_required(VERSION 3.27)
project(PgnStats C)

set(CMAKE_C_STANDARD 11)

find_package(Curses REQUIRED)

include_directories(src)

add_executable(PgnStats
        src/individual.c
        src/individual.h
        src/main.c
        src/statistics.c
        src/statistics.h
        src/types.h
        src/util.c
        src/util.h)

target_link_libraries(PgnStats ${CURSES_LIBRARIES})
target_include_directories(PgnStats PRIVATE ${CURSES_INCLUDE_DIRS})