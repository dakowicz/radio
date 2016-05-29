//
// Created by tomasz on 28.05.16.
//

#ifndef SERVER_SOUNDPROCESSOR_H
#define SERVER_SOUNDPROCESSOR_H


#include "AtomicMap.h"
#include "ClientManager.h"
#include "FileManager.h"
#include "PlaylistManager.h"

class SoundProcessor {
public:

    SoundProcessor(const std::shared_ptr<FileManager> &fileManager,
                       const std::shared_ptr<PlaylistManager> &playlistManager, const std::shared_ptr< AtomicMap<int, ClientManager* > > &clients);

    void stream();

private:

    std::shared_ptr<AtomicMap<int, ClientManager*>> clients;

    std::shared_ptr<FileManager> fileManager;

    std::shared_ptr<PlaylistManager> playlistManager;

    bool running;

    void log(std::string message);

    static std::chrono::milliseconds TIME_INTERVAL_MS;

    static int PACKAGE_SIZE_B;

    static std::string MODULE_NAME;

    void broadcastToClients(Data *data);

    void divideFile(std::shared_ptr<std::ifstream> fileStream);

    bool endOf(std::shared_ptr<std::ifstream> fileStream) const;

    void pushStreamMessage(std::shared_ptr<std::ifstream> fileStream);

    Data * readFile(std::shared_ptr<std::ifstream> &fileStream, unsigned char *streamData) const;
};


#endif //SERVER_SOUNDPROCESSOR_H
