//
// Created by tomasz on 05.05.16.
//

#include <cstdlib>
#include <iostream>
#include "ConnectionManager.h"
#include "Dispatcher.h"

void print(const char *message);

int main(int argc, char* arg[])
{
    int port = atoi(arg[1]);
    std::thread *dispatcherThread, *connectionManagerThread;

    Dispatcher* dispatcher = new Dispatcher();
    print("Dispatcher is created");

    ConnectionManager* connectionManager = new ConnectionManager(dispatcher, port);
    print("ConnectionManager is created");

    dispatcherThread = new std::thread(&Dispatcher::start, dispatcher);
    connectionManagerThread = new std::thread(&ConnectionManager::start, connectionManager);

    dispatcherThread->join();
    connectionManagerThread->join();

    print("Application has been closed");

    return 0;
}

void print(const char *message) { std::cout << message << std::endl; }
