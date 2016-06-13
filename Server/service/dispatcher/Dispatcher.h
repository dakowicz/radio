//
// Created by tomasz on 05.05.16.
//

#ifndef SERVER_DISPATCHER_H
#define SERVER_DISPATCHER_H

#include "../connection/ClientManager.h"
#include "../connection/domain/ClientsMap.h"
#include "../file/FileManager.h"
#include "../playlist/PlaylistManager.h"
#include "domain/FileType.h"

class ClientManager;

class Dispatcher {
public:

    Dispatcher(FileManager &fileManager, PlaylistManager &playlistManager, const std::shared_ptr<ClientsMap<int, ClientManager *>> &clients) :
            fileManager(fileManager), playlistManager(playlistManager), clients(clients), atomicQueue(MODULE_NAME), logger(MODULE_NAME){};

    void start();

    void addMessage(std::shared_ptr<Data> newMessage);

    const bool isRunning() const { return running.load(); }

    void setRunning(bool val) { this->running = val; }

private:

    std::shared_ptr<ClientsMap<int, ClientManager *>> clients;

    static std::string MODULE_NAME;

    std::atomic<bool> running;

    AtomicQueue<std::shared_ptr<Data>> atomicQueue;

    FileManager &fileManager;

    PlaylistManager &playlistManager;

    Logger logger;

    void wrongDataType();

    bool isMessageEmpty(std::shared_ptr<Data> newMessage) const;

    void processVote(std::shared_ptr<Data> data);

    void processFile(std::shared_ptr<Data> data);

    void processConnectionMessage(std::shared_ptr<Data> data);

    void processMessage(std::shared_ptr<Data> data);

    int getSongID(std::shared_ptr<Data> data) const;

    void broadcastPlaylist();

    void getPlaylistCSV(std::string &content);

    void getSongData(std::shared_ptr<Data> &data, std::string &author, std::string &title);

    std::string addNewMusicFile(const std::shared_ptr<Data> &data, const std::string &author, const std::string &title) const;

    void processMusicFile(std::shared_ptr<Data> data);
};


#endif //SERVER_DISPATCHER_H
