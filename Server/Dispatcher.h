//
// Created by tomasz on 05.05.16.
//

#ifndef SERVER_DISPATCHER_H
#define SERVER_DISPATCHER_H

#include <thread>
#include <atomic>
#include "FileManager.h"
#include "Data.h"
#include "PlaylistManager.h"


class Dispatcher {
public:

    Dispatcher(FileManager &fileManager, PlaylistManager &playlistManager) :
            fileManager(fileManager), playlistManager(playlistManager), atomicQueue(MODULE_NAME), logger(MODULE_NAME){};

    void start();

    void addMessage(Data *newMessage);

    const bool isRunning() const { return running.load(); }

    void setRunning(bool val) { this->running = val; }

private:

    static std::string MODULE_NAME;

    void wrongDataType();

    std::atomic<bool> running;

    AtomicQueue<Data*> atomicQueue;

    FileManager &fileManager;

    PlaylistManager &playlistManager;

    Logger logger;

    bool isMessageEmpty(Data *newMessage) const;

    void processVote(Data *data);

    void processMusicFile(Data *data);

    void processConnectionMessage(Data *data);

    void processMessage(Data *data);
};


#endif //SERVER_DISPATCHER_H
