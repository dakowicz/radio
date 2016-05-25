//
// Created by tomasz on 05.05.16.
//

#include <cstdlib>
#include <iostream>
#include "ConnectionManager.h"

void log(const char *message);

void print(const char *message);

int main(int argc, char* arg[])
{
    int port = atoi(arg[1]);
    std::thread *dispatcherThread, *connectionManagerThread;

    Dispatcher* dispatcher = new Dispatcher();
<<<<<<< Updated upstream
    print("Dispatcher is created");

    ConnectionManager* connectionManager = new ConnectionManager(dispatcher, port);
    print("ConnectionManager is created");
=======
    log("Dispatcher is created");

    ConnectionManager* connectionManager = new ConnectionManager(dispatcher, port);
    log("ConnectionManager is created");
>>>>>>> Stashed changes

    dispatcherThread = new std::thread(&Dispatcher::start, dispatcher);
    connectionManagerThread = new std::thread(&ConnectionManager::start, connectionManager);

    dispatcherThread->join();
    connectionManagerThread->join();

<<<<<<< Updated upstream
    print("Application has been closed");
=======
    log("Application has been closed");
>>>>>>> Stashed changes

    return 0;
}

<<<<<<< Updated upstream
void print(const char *message) { std::cout << message << std::endl; }
=======
void log(const char *message) { std::cout << message << std::endl; }
>>>>>>> Stashed changes
