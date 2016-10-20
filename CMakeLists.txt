cmake_minimum_required(VERSION 3.6)
project(a)

set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -std=c11")

set(SOURCE_FILES
    "goto_link_store.c"
    "goto_link_store.h"
    main.c)

add_executable(a ${SOURCE_FILES})