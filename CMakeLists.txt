cmake_minimum_required(VERSION 3.5)
project(radio)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Server/main.cpp Server/Header.cpp Server/Header.h)
add_executable(Server ${SOURCE_FILES} Server/Header.cpp Server/Header.h)