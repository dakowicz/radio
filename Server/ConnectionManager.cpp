//
// Created by tomasz on 05.05.16.
//


#include <cstring>
#include <unistd.h>
#include "ConnectionManager.h"

const int ConnectionManager::QUEUE_LIMIT = 5;

const int ConnectionManager::READ_TIMEOUT_SEC = 2;

const std::string ConnectionManager::MODULE_NAME = "ConnectionManager";

ConnectionManager::~ConnectionManager() {
    close(this->socketDescriptor);
}

void ConnectionManager::start() {
    int serverSocketDescriptor;
    int newSocketDescriptor;
    socklen_t clilen;
    sockaddr_in serv_addr;
    sockaddr_in cli_addr;
    fd_set readSet;

    clilen = sizeof(cli_addr);
    initConfig(serverSocketDescriptor, serv_addr, cli_addr);
    if(bind(serverSocketDescriptor, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        handleError("error on binding");
    }
    if(listen(serverSocketDescriptor, QUEUE_LIMIT) == -1) {
        handleError("error on listening");
    }
    Data *data1 = new Data(DataType::CONNECTION, new char[10], 10);
    Data *data2 = new Data(DataType::MUSIC_FILE, new char[10], 10);
    Data *data3 = new Data(DataType::VOTE, new char[10], 10);
    Data *data4 = new Data((DataType)1, new char[10], 10);

    dispatcher.addMessage(data1);
    dispatcher.addMessage(data2);
    dispatcher.addMessage(data3);
    dispatcher.addMessage(data4);
    dispatcher.addMessage(nullptr);

    this->running = true;
    while(isRunning()) {
        readSet = selectInit(serverSocketDescriptor, readSet);
        int max_sd = serverSocketDescriptor;
        registerSockets(readSet, max_sd);

        int activity = select( max_sd + 1 , &readSet , NULL , NULL , NULL);
        if (isSelectError(activity)) {
            perror("select error");
        }

        if (isNewClient(serverSocketDescriptor, readSet)) {
            newSocketDescriptor = acceptNewClient(serverSocketDescriptor, clilen, cli_addr);
            checkSocketDescriptor(newSocketDescriptor);
        }
        checkAllSocketsForIncomingData(readSet);
    }
    closeClientManagers();
}

void ConnectionManager::checkAllSocketsForIncomingData(fd_set &readSet) const {
    std::vector<int> clientSockets;
    getClientSockets(clientSockets);
    for(int actualSocket: clientSockets) {
        ClientManager *clientManager = clients->get(actualSocket);
        if (isDataOnSocket(actualSocket, readSet)) {
            clientManager->addReadRequest();
        } else {
            clientManager->setNoReadRequests();
        }
    }
}

void ConnectionManager::registerSockets(fd_set &readSet, int &max_sd) const {
    std::vector<int> clientSockets;
    getClientSockets(clientSockets);
    for (int socket : clientSockets) {
        FD_SET(socket, &readSet);
        if (socket > max_sd) {
            max_sd = socket;
        }
    }
}

void ConnectionManager::getClientSockets(std::vector<int> &clientSockets) const { clients->getAllKeys(clientSockets); }

bool ConnectionManager::isDataOnSocket(int actualSocket, fd_set &readSet) const { return FD_ISSET(actualSocket , &readSet); }

void ConnectionManager::checkSocketDescriptor(int newSocketDescriptor) {
    if (newSocketDescriptor < 0) {
        handleError("error on accept");
    } else {
        setNonBlockingSocketState(newSocketDescriptor);
        addClient(newSocketDescriptor);
    }
}

int ConnectionManager::acceptNewClient(int serverSocketDescriptor, socklen_t &clilen, sockaddr_in &cli_addr) const {
    int newSocketDescriptor;
    newSocketDescriptor = accept(serverSocketDescriptor, (struct sockaddr *) &cli_addr, &clilen);
    return newSocketDescriptor;
}

bool ConnectionManager::isNewClient(int serverSocketDescriptor, fd_set &readSet) const { return FD_ISSET(serverSocketDescriptor, &readSet); }

fd_set &ConnectionManager::selectInit(int serverSocketDescriptor, fd_set &readSet) const {
    FD_ZERO(&readSet);
    FD_SET(serverSocketDescriptor, &readSet);
    return readSet;
}

bool ConnectionManager::isSelectError(int activity) const { return (activity < 0) && (errno != EINTR); }

void ConnectionManager::setNonBlockingSocketState(int newSocketDescriptor) const {
    struct timeval timeout = setTimeout(timeout);
    if (setsockopt (newSocketDescriptor, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0) {
        perror("setsockopt failed\n");
    }
    if (setsockopt (newSocketDescriptor, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) < 0) {
        perror("setsockopt failed\n");
    }

}

timeval &ConnectionManager::setTimeout(timeval &timeout) const {
    timeout.tv_sec = READ_TIMEOUT_SEC;
    timeout.tv_usec = 0;
    return timeout;
}

void ConnectionManager::closeClientManagers() {
    std::vector<ClientManager*> clientManagers;
    clients->getAllValues(clientManagers);
    for(auto& clientManager : clientManagers) {
        std::thread *&clientThread = clientManagersThreads[clientManager->getSocketDescriptor()];
        if(clientThread != nullptr && clientThread->joinable()) {
            clientThread->join();
        }
    }
}

void ConnectionManager::addClient(int newSocketDescriptor) {
    ClientManager *clientManager = new ClientManager(dispatcher, newSocketDescriptor);
    clientManagersThreads[newSocketDescriptor] = new std::thread(&ClientManager::handle, clientManager, clients);
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


