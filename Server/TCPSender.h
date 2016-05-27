//
// Created by tomasz on 24.05.16.
//

#ifndef SERVER_TCPSENDER_H
#define SERVER_TCPSENDER_H

#include <string>

class TCPSender {
public:

    TCPSender(int socketDescriptor);

    ~TCPSender();

    void sendMusic(unsigned char *string);

    void sendVotes(unsigned char *string);

    void sendConnectionInfo(unsigned char *message);

private:

    int socketDescriptor;

    static std::string MODULE_NAME;

    void send(unsigned char *header, unsigned char *message);

    void addMessage(unsigned char *message, unsigned char *dataToSend) const;

    void addHeader(unsigned char *header, unsigned char *dataToSend) const;
};


#endif //SERVER_TCPSENDER_H
