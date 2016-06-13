//
// Created by tomasz on 05.05.16.
//

#ifndef SERVER_CONNECTIONMANAGER_H
#define SERVER_CONNECTIONMANAGER_H


#include <netinet/in.h>
#include "../../service/connection/ClientManager.h"


class ConnectionManager {
public:

    ConnectionManager(Dispatcher *dispatcher, int port, const std::shared_ptr<ClientsMap<int, ClientManager *>> &clients) :
            dispatcher(dispatcher), port(port), clients(clients){};

    ~ConnectionManager();

    void start();

    const bool isRunning() const { return running.load(); }

    void setRunning(bool val) { this->running = val; }

private:

    void initConfig(int &sockfd, sockaddr_in &serv_addr, sockaddr_in &cli_addr);

    void addClient(int newSocketDescriptor);

    void handleError(const char *errorMessage) const;

    int port;

    int socketDescriptor;

    Dispatcher *dispatcher;

    std::shared_ptr<ClientsMap<int, ClientManager *>> clients;

    std::atomic<bool> running;

    static const std::string MODULE_NAME;

    static const int QUEUE_LIMIT;

    std::map<int, std::thread*> clientManagersThreads;

    void closeClientManagers();

    void setNonBlockingSocketState(int newSocketDescriptor) const;

    timeval &setTimeout(timeval &timeout) const;

    void registerSockets(fd_set &readSet, int &max_sd) const;

    bool isSelectError(int activity) const;

    fd_set &selectInit(int serverSocketDescriptor, fd_set &readSet) const;

    bool isNewClient(int serverSocketDescriptor, fd_set &readSet) const;

    int acceptNewClient(int serverSocketDescriptor, socklen_t &clilen, sockaddr_in &cli_addr) const;

    void checkSocketDescriptor(int newSocketDescriptor);

    bool isDataOnSocket(int actualSocket, fd_set &readSet) const;

    void checkAllSocketsForIncomingData(fd_set &readSet) const;

    void getClientSockets(std::vector<int> &clientSockets) const;

    static const int READ_TIMEOUT_SEC;

    void broadcastPlaylist() const;
};


#endif //SERVER_CONNECTIONMANAGER_H
