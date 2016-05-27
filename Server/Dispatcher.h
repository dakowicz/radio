//
// Created by tomasz on 05.05.16.
//

#ifndef SERVER_DISPATCHER_H
#define SERVER_DISPATCHER_H


#include "Data.h"
#include "AtomicQueue.h"
#include "FileReceiver.h"
#include "PlaylistManager.h"
#include <thread>

class PlaylistManager;

class Dispatcher {

public:

    Dispatcher(const std::shared_ptr<FileReceiver> &fileReceiver, const std::shared_ptr<PlaylistManager> &playlistManager);

    ~Dispatcher();

    void start();

    void addMessage(Data *newMessage);

private:

    void wrongDataType();

    bool running;

    std::shared_ptr<AtomicQueue<Data*>> atomicQueue;

    static std::string MODULE_NAME;

    void log(std::string message) const;

    std::shared_ptr<FileReceiver> fileReceiver;

    std::shared_ptr<PlaylistManager> playlistManager;

    void processMessage(const std::shared_ptr<Data> &data);

    void processVote(const std::shared_ptr<Data> &data);

    void processMusicFile(const std::shared_ptr<Data> &data);

    void processConnectionMessage(const std::shared_ptr<Data> &data);

    bool isMessageEmpty(Data *newMessage) const;

    void processVote(Data *data);

    void processMusicFile(Data *data);

    void processConnectionMessage(Data *data);

    void processMessage(Data *data);
};


#endif //SERVER_DISPATCHER_H
