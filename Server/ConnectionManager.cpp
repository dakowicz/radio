//
// Created by tomasz on 05.05.16.
//


#include <cstring>
#include <unistd.h>
#include "ConnectionManager.h"

int ConnectionManager::QUEUE_LIMIT = 5;

std::string ConnectionManager::MODULE_NAME = "ConnectionManager";

ConnectionManager::ConnectionManager(const std::shared_ptr<Dispatcher> &dispatcher, int port,
                                     const std::shared_ptr< AtomicMap<int, ClientManager* > > &clients) {
    this->port = port;
    this->dispatcher = dispatcher;
    this->clients = clients;
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
    if(bind(serverSocketDescriptor, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        handleError("error on binding");
    }
    if(listen(serverSocketDescriptor, QUEUE_LIMIT) == -1) {
        handleError("error on listening");
    }


//    std::shared_ptr<Data> data1 = std::make_shared<Data>(DataType::CONNECTION, new unsigned char[10]);
//    std::shared_ptr<Data> data2 = std::make_shared<Data>(DataType::MUSIC_FILE, new unsigned char[10]);
//    std::shared_ptr<Data> data3 = std::make_shared<Data>(DataType::VOTE, new unsigned char[10]);
//    std::shared_ptr<Data> data4 = std::make_shared<Data>(DataType::STREAM, new unsigned char[10]);
    Data *data1 = new Data(DataType::CONNECTION, new unsigned char[10]);
    Data *data2 = new Data(DataType::MUSIC_FILE, new unsigned char[10]);
    Data *data3 = new Data(DataType::VOTE, new unsigned char[10]);
    Data *data4 = new Data(DataType::STREAM, new unsigned char[10]);

    dispatcher->addMessage(data1);
    dispatcher->addMessage(data2);
    dispatcher->addMessage(data3);
    dispatcher->addMessage(data4);
    dispatcher->addMessage(nullptr);

    addClient(4);
    addClient(5);

    this->running = true;

    while(running) {
        newSocketDescriptor = accept(serverSocketDescriptor, (struct sockaddr *) &cli_addr, &clilen);
        if(newSocketDescriptor < 0) {
            handleError("error on accept");
        } else {
            addClient(newSocketDescriptor);
        }
    }
}

void ConnectionManager::addClient(int newSocketDescriptor) {
    clientManagers.push_back(std::make_shared<ClientManager>(dispatcher, newSocketDescriptor));
    new std::thread(&ClientManager::handle, clientManagers.back().get(), clients);
}

void ConnectionManager::initConfig(int &sockfd, sockaddr_in &serv_addr, sockaddr_in &cli_addr) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
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







