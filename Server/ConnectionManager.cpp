//
// Created by tomasz on 05.05.16.
//


#include <cstring>
#include <unistd.h>
#include "ConnectionManager.h"

int ConnectionManager::QUEUE_LIMIT = 5;

ConnectionManager::ConnectionManager(Dispatcher *dispatcher, int port) {
    this->port = port;
    this->dispatcher = dispatcher;
    this->clientThreads = new BlockingMap<int, ClientManager*>;
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

    initConfig(serverSocketDescriptor, serv_addr, cli_addr);

    if (bind(serverSocketDescriptor, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        handleError("error on binding");
    }

    if(listen(serverSocketDescriptor, QUEUE_LIMIT) == -1) {
        handleError("error on listening");
    }

    dispatcher->addMessage(new Data(DataType::CONNECTION, new unsigned char(10)));
    dispatcher->addMessage(new Data(DataType::VOTE, new unsigned char(10)));
    dispatcher->addMessage(new Data(DataType::MUSIC_FILE, new unsigned char(10)));
    dispatcher->addMessage(new Data(DataType::STREAM, new unsigned char(10)));

    addClient(4);

    this->running = true;

    while(running) {
        newSocketDescriptor = accept(serverSocketDescriptor, (struct sockaddr *) &cli_addr, &clilen);
        if (newSocketDescriptor < 0) {
            handleError("error on accept");
        } else {
            addClient(newSocketDescriptor);
        }
    }
}

void ConnectionManager::addClient(int newSocketDescriptor) {
    new std::thread(&ClientManager::handle, new ClientManager(dispatcher, newSocketDescriptor), clientThreads);
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
    //TODO
    perror(errorMessage);
    exit(0);
}

