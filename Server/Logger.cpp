//
// Created by tomasz on 31.05.16.
//

#include <iostream>
#include "Logger.h"

std::mutex Logger::mutex;

void Logger::log(std::string message) const {
    std::unique_lock<std::mutex> lock(mutex);
    logModuleName();
    logSocketDescriptor();
    logMessage(message);
    logEnding();
    lock.unlock();
}

void Logger::logEnding() const { std::cout << std::endl << std::flush; }

void Logger::logMessage(const std::string &message) const {
    if(!message.empty()){
        std::cout << ": " << message;
    }
}

void Logger::logSocketDescriptor() const {
    if(socketDescriptor != 0){
        std::cout << socketDescriptor;
    }
}

void Logger::logModuleName() const { std::cout << moduleName; }








