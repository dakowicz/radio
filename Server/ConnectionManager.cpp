//
// Created by tomasz on 05.05.16.
//


#include <cstring>
#include <unistd.h>
#include "ConnectionManager.h"
#include "Sender.h"
#include "ClientManager.h"

int ConnectionManager::QUEUE_LIMIT = 5;

ConnectionManager::ConnectionManager(Dispatcher *dispatcher, int port) {
    this->port = port;
    this->dispatcher = dispatcher;
}

ConnectionManager::~ConnectionManager() {
    close(this->socketDescriptor);
}

void ConnectionManager::start() {
    int serverSocketDescriptor;
    int newSocketDescriptor;
    socklen_t clilen;
    sockaddr_in serv_addr;
    sockaddr_in cli_addr;
    clilen = sizeof(cli_addr);
    fd_set readSet;

    initConfig(serverSocketDescriptor, serv_addr, cli_addr);

    if (bind(serverSocketDescriptor, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        handleError("error on binding");
    }

    if(listen(serverSocketDescriptor, QUEUE_LIMIT) == -1) {
        handleError("error on listening");
    }

    while(true) {

        //clear the socket set
        FD_ZERO(&readSet);

        //add server socket to set
        FD_SET(serverSocketDescriptor, &readSet);
        int max_sd = serverSocketDescriptor;

        //add child sockets to set
        for (int actualSocket : clientSockets) {

            //if valid socket descriptor then add to read list
            //if(actualSocket > 0)
            FD_SET( actualSocket , &readSet);

            //highest file descriptor number, need it for the select function
            if(actualSocket > max_sd)
                max_sd = actualSocket;
        }

        //wait for an activity on one of the sockets , timeout is NULL , so wait indefinitely
        int activity = select( max_sd + 1 , &readSet , NULL , NULL , NULL);

        if ((activity < 0) && (errno!=EINTR)) {
            perror("select error");
        }

        //If something happened on the master socket , then its an incoming connection
        if (FD_ISSET(serverSocketDescriptor, &readSet)) {

            newSocketDescriptor = accept(serverSocketDescriptor, (struct sockaddr *) &cli_addr, &clilen);
            if (newSocketDescriptor < 0) {
                handleError("error on accept");
            } else {
                addClient(newSocketDescriptor);
                clientSockets.push_back(newSocketDescriptor);
                //TODO delete socket from vector after connection is finished
            }
        }
        for(int actualSocket: clientSockets){
            if (FD_ISSET( actualSocket , &readSet)) {
                //TODO notify socketListner...
            }
        }
    }
}

void ConnectionManager::addClient(int newSocketDescriptor) {
    std::thread *clientThread = new std::thread(handleClient, newSocketDescriptor, this->dispatcher);
    clientThreads[newSocketDescriptor] = clientThread;
    //TODO delete client from map
}

void ConnectionManager::handleClient(int newSocketDescriptor, Dispatcher *dispatcher) {
    ClientManager *clientManager = new ClientManager(dispatcher, newSocketDescriptor);
    clientManager->handle();
}

void ConnectionManager::initConfig(int &sockfd, sockaddr_in &serv_addr, sockaddr_in &cli_addr) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        handleError("error opening socket");
    }
    this->socketDescriptor = sockfd;
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons((uint16_t) port);
}

void ConnectionManager::handleError(const char *errorMessage) const {
    //TODO error handling
    perror(errorMessage);
    exit(0);
}

