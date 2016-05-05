//
// Created by tomasz on 05.05.16.
//

#ifndef SERVER_SOCKETLISTENER_H
#define SERVER_SOCKETLISTENER_H


class SocketListener {

public:
    SocketListener(int socketDescriptor);
    ~SocketListener();
    void handle();

private:
    int socketDescriptor;
};

#endif //SERVER_SOCKETLISTENER_H
