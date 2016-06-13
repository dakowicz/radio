cmake_minimum_required(VERSION 3.5)
project(Server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

set(SOURCE_FILES
    CMakeLists.txt
    Dispatcher.cpp
    Dispatcher.h
    Header.cpp
    Header.h AtomicQueue.h ClientsMap.h Application.cpp ConnectionManager.cpp ConnectionManager.h Sender.cpp Sender.h SocketListener.cpp SocketListener.h Data.cpp Data.h ClientManager.cpp ClientManager.h TCPSender.cpp TCPSender.h DataType.h TCPListener.cpp TCPListener.h SoundProcessor.cpp SoundProcessor.h FileManager.cpp FileManager.h PlaylistManager.cpp PlaylistManager.h Song.cpp Song.h PlaylistFileReader.cpp PlaylistFileReader.h ConnectionType.h Logger.cpp Logger.h SongList.cpp SongList.h VoteType.h FileType.h)

add_executable(Server ${SOURCE_FILES})