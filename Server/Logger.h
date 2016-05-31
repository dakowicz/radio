//
// Created by tomasz on 31.05.16.
//

#ifndef SERVER_LOGGER_H
#define SERVER_LOGGER_H


#include <mutex>

class Logger {
public:

    Logger(std::string moduleName) : moduleName(moduleName), socketDescriptor(){};

    Logger(std::string moduleName, int socketDescriptor) : moduleName(moduleName), socketDescriptor(socketDescriptor){};

    void log(std::string message) const;

private:

    static std::mutex mutex;

    std::string moduleName;

    int socketDescriptor;

    void logModuleName() const;

    void logSocketDescriptor() const;

    void logMessage(const std::string &message) const;

    void logEnding() const;
};


#endif //SERVER_LOGGER_H
