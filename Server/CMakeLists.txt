cmake_minimum_required(VERSION 3.5)
project(Server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

set(SOURCE_FILES
    CMakeLists.txt
    Header.cpp
    Header.h
    Application.cpp ConnectionManager.cpp ConnectionManager.h Dispatcher.cpp Dispatcher.h Sender.cpp Sender.h SocketListener.cpp SocketListener.h Data.cpp Data.h ClientManager.cpp ClientManager.h TCPSender.cpp TCPSender.h DataType.h TCPListener.cpp TCPListener.h BlockingQueue.h BlockingMap.h)

add_executable(Server ${SOURCE_FILES})