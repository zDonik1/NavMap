cmake_minimum_required(VERSION 2.8)

project(NavMap)

set(SOURCE_FILES
    "main.cpp"
    "singlelist.h"
    "stack.h"
    "adjlistnondirgraph.h"
    )

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
