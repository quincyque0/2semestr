cmake_minimum_required(VERSION 3.10)
project(WordReverser)

set(CMAKE_C_STANDARD 11)

option(LIB_TYPE "Type of library to build (STATIC or SHARED)" STATIC)

if(LIB_TYPE STREQUAL "SHARED")
    add_library(MY_LOG SHARED
        secondary.c
        header.h
    )
else()
    add_library(MY_LOG STATIC
        secondary.c
        header.h
    )
endif()

set_target_properties(MY_LOG PROPERTIES 
    LINKER_LANGUAGE C            
    POSITION_INDEPENDENT_CODE ON      
)

add_executable(program main.c)

target_link_libraries(program PRIVATE MY_LOG)

configure_file(../FourLab.txt ${CMAKE_CURRENT_BINARY_DIR}/FourLab.txt COPYONLY)