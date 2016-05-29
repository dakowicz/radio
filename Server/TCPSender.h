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

    void sendMusic(unsigned char *string, int messageSize);

    void sendVotes(unsigned char *string, int messageSize);

    void sendConnectionInfo(unsigned char *message, int messageSize);

private:

    int socketDescriptor;

    static std::string MODULE_NAME;

    void send(unsigned char *header, unsigned char *message, int messageSize);

    void addMessage(unsigned char *message, unsigned char *dataToSend, size_t messageSize) const;

    void addHeader(unsigned char *header, unsigned char *dataToSend) const;

    void log(std::string message);

    void writeData(const unsigned char *dataToSend, int dataToSendSize) const;

    int getHeaderSize() const;
};


#endif //SERVER_TCPSENDER_H
