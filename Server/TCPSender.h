//
// Created by tomasz on 24.05.16.
//

#ifndef SERVER_TCPSENDER_H
#define SERVER_TCPSENDER_H


class TCPSender {

public:
    TCPSender(int socketDescriptor);
    ~TCPSender();

    int socketDescriptor;

    void sendMusic(unsigned char *string);

    void sendVotes(unsigned char *string);

    void sendConnectionInfo(uint8_t *message);

    void send(uint8_t *header, uint8_t *message);
};


#endif //SERVER_TCPSENDER_H
