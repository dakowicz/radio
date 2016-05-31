//
// Created by tomasz on 05.05.16.
//

#include <cstdlib>
#include <iostream>
#include "SoundProcessor.h"
#include "ConnectionManager.h"


int main(int argc, char *arg[]) {

    int port = atoi(arg[1]);
    std::string fileSystemPrefix = std::string(arg[2]);
    Logger logger("Application");

    std::shared_ptr< AtomicMap<int, ClientManager *> > clients = std::make_shared< AtomicMap<int, ClientManager *> >("Clients");

    FileManager fileManager(fileSystemPrefix);
    PlaylistManager playlistManager(fileSystemPrefix);

    Dispatcher dispatcher(fileManager, playlistManager);
    std::thread dispatcherThread = std::thread(&Dispatcher::start, &dispatcher);
    logger.log("Dispatcher has been created");

    ConnectionManager connectionManager(dispatcher, port, clients);
    std::thread connectionManagerThread = std::thread(&ConnectionManager::start, &connectionManager);
    logger.log("ConnectionManager has been created");

    SoundProcessor soundProcessor(fileManager, playlistManager, clients);
    std::thread soundProcessorThread = std::thread(&SoundProcessor::stream, &soundProcessor);
    logger.log("SoundProcessor has been created");

    connectionManagerThread.join();
    dispatcherThread.join();
    soundProcessorThread.join();

    logger.log("Has been closed");
    return 0;
}