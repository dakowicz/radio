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

    void sendMusic(char *message, int messageSize);

    void sendVotes(char *message, int messageSize);

    void sendConnectionInfo(char *message, int messageSize);

private:

    int socketDescriptor;

    static std::string MODULE_NAME;

    void send(char *header, char *message, int messageSize);

    void addMessage(char *message, char *dataToSend, size_t messageSize) const;

    void addHeader(char *header, char *dataToSend) const;

//    std::ofstream *file;

    void log(std::string message);

    void writeData(char *dataToSend, int dataToSendSize) const;

    int getHeaderSize() const;
};


#endif //SERVER_TCPSENDER_H
