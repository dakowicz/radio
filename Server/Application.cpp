//
// Created by tomasz on 05.05.16.
//

#include <cstdlib>
#include <iostream>
#include "ConnectionManager.h"


void log(std::string message);

int main(int argc, char* arg[]) {
    std::thread *dispatcherThread, *connectionManagerThread;
    int port = atoi(arg[1]);

    Dispatcher* dispatcher = new Dispatcher();
    dispatcherThread = new std::thread(&Dispatcher::start, dispatcher);
    log("Dispatcher is created");

    ConnectionManager* connectionManager = new ConnectionManager(dispatcher, port);
    connectionManagerThread = new std::thread(&ConnectionManager::start, connectionManager);
    log("ConnectionManager is created");

    dispatcherThread->join();
    connectionManagerThread->join();
    log("Application has been closed");

    return 0;
}

void log(std::string message) {
    std::cout << message << std::endl << std::flush;
}
