//
// Created by tomasz on 05.05.16.
//

#ifndef SERVER_DISPATCHER_H
#define SERVER_DISPATCHER_H

#include "ClientManager.h"
#include "ClientsMap.h"
#include "FileManager.h"
#include "PlaylistManager.h"

class ClientManager;

class Dispatcher {
public:

    Dispatcher(FileManager &fileManager, PlaylistManager &playlistManager, const std::shared_ptr<ClientsMap<int, ClientManager *>> &clients) :
            fileManager(fileManager), playlistManager(playlistManager), clients(clients), atomicQueue(MODULE_NAME), logger(MODULE_NAME){};

    void start();

    void addMessage(Data *newMessage);

    const bool isRunning() const { return running.load(); }

    void setRunning(bool val) { this->running = val; }

private:

    std::shared_ptr<ClientsMap<int, ClientManager *>> clients;

    static std::string MODULE_NAME;

    std::atomic<bool> running;

    AtomicQueue<Data*> atomicQueue;

    FileManager &fileManager;

    PlaylistManager &playlistManager;

    Logger logger;

    void wrongDataType();

    bool isMessageEmpty(Data *newMessage) const;

    void processVote(Data *data);

    void processMusicFile(Data *data);

    void processConnectionMessage(Data *data);

    void processMessage(Data *data);

    int getSongID(const Data *data) const;

    void getPlaylistCSV(std::string content, int &size);

    void broadcastPlaylist();

    void getPlaylistCSV(std::string &content, int &size);

    void getPlaylistCSV(std::string &content);
};


#endif //SERVER_DISPATCHER_H
