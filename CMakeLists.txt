cmake_minimum_required(VERSION 2.8)

project(NavMap)

set(SOURCE_FILES
    "main.cpp"
    "circsinglelist.h"
    "stack.h"
    "adjlistnondirgraph.h"
    "adjlistnondirgraph.cpp"
    "queue.h"
    "map.h"
    "map.cpp"
    "vector2.h"
    "vector2.cpp"
    "io.h"
    "io.cpp"
    )

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
