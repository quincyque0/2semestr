cmake_minimum_required(VERSION 3.10)	  
										                   
project(LIBS)			

set(SOURCE_EXE main.c)		
set(SOURCE_LIB second.c)			

add_library(MY_LOG STATIC ${SOURCE_LIB})	

add_executable(main ${SOURCE_EXE})	

target_link_libraries(main MY_LIB)		