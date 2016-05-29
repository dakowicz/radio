//
// Created by tomasz on 05.05.16.
//

#include <cstdlib>
#include <iostream>
#include "ConnectionManager.h"
#include "SoundProcessor.h"

void log(std::string message);

int main(int argc, char *arg[]) {

    int port = atoi(arg[1]);
    std::string fileSystemPrefix = std::string(arg[2]);

    std::shared_ptr< AtomicMap<int, ClientManager*> > clients = std::make_shared< AtomicMap<int, ClientManager*> >("Clients");

    std::shared_ptr<FileManager> fileManager = std::make_shared<FileManager>(fileSystemPrefix);
    std::shared_ptr<PlaylistManager> playlistManager = std::make_shared<PlaylistManager>();
    std::shared_ptr<FileReceiver> fileReceiver = std::make_shared<FileReceiver>(fileManager);

    std::shared_ptr<Dispatcher> dispatcher = std::make_shared<Dispatcher>(fileReceiver, playlistManager);
    std::thread dispatcherThread = std::thread(&Dispatcher::start, dispatcher.get());
    log("Dispatcher has been created");

    std::shared_ptr<ConnectionManager> connectionManager = std::make_shared<ConnectionManager>(dispatcher, port, clients);
    std::thread connectionManagerThread = std::thread(&ConnectionManager::start, connectionManager.get());
    log("ConnectionManager has been created");

    std::shared_ptr<SoundProcessor> soundProcessor = std::make_shared<SoundProcessor>(fileManager, playlistManager, clients);
    std::thread soundProcessorThread = std::thread(&SoundProcessor::stream, soundProcessor.get());
    log("SoundProcessor has been created");

    connectionManagerThread.join();
    dispatcherThread.join();
    soundProcessorThread.join();

    log("Application has been closed");
    return 0;
}

void log(std::string message) {
    std::cout << message << std::endl << std::flush;
}
