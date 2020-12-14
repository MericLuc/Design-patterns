cmake_minimum_required(VERSION 3.6)
project(Mediator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(EXECUTABLE_OUTPUT_PATH .)

message( STATUS "Building project ${PROJECT_NAME}")

set(HEADER_FILES
        ChatRoom.hpp
        Person.hpp 
)

set(SOURCE_FILES 
        main.cpp
        Person.cpp 
        ChatRoom.cpp 
)

add_executable( Mediator ${SOURCE_FILES} ${HEADER_FILES} )