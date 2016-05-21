//
// Created by tomasz on 05.05.16.
//

#include <cstdlib>
#include "ConnectionManager.h"
#include "Dispatcher.h"

int main(int argc, char* arg[])
{
    int port = atoi(arg[1]);

    Dispatcher* dispatcher = new Dispatcher();
    dispatcher->startHandling();

    ConnectionManager* connectionManager = new ConnectionManager(dispatcher, port);
    connectionManager->start();

    return 0;
}
