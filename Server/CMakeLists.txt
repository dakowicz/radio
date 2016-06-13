cmake_minimum_required(VERSION 3.5)
project(Server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

set(SOURCE_FILES
    CMakeLists.txt
        service/dispatcher/Dispatcher.cpp
        service/dispatcher/Dispatcher.h
        tcp/domain/Header.cpp
        tcp/domain/Header.h service/dispatcher/domain/AtomicQueue.h service/connection/domain/ClientsMap.h Application.cpp tcp/connection/ConnectionManager.cpp tcp/connection/ConnectionManager.h service/sender/Sender.cpp service/sender/Sender.h service/receiver/SocketListener.cpp service/receiver/SocketListener.h service/dispatcher/domain/Data.cpp service/dispatcher/domain/Data.h service/connection/ClientManager.cpp service/connection/ClientManager.h tcp/sender/TCPSender.cpp tcp/sender/TCPSender.h service/dispatcher/domain/DataType.h tcp/receiver/TCPListener.cpp tcp/receiver/TCPListener.h service/streamer/SoundProcessor.cpp service/streamer/SoundProcessor.h service/file/FileManager.cpp service/file/FileManager.h service/playlist/PlaylistManager.cpp service/playlist/PlaylistManager.h service/playlist/domain/Song.cpp service/playlist/domain/Song.h service/playlist/PlaylistFileReader.cpp service/playlist/PlaylistFileReader.h logger/Logger.cpp logger/Logger.h service/playlist/domain/SongList.cpp service/playlist/domain/SongList.h service/dispatcher/domain/VoteType.h service/dispatcher/domain/FileType.h)

add_executable(Server ${SOURCE_FILES})