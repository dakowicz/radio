//
// Created by tomasz on 31.05.16.
//

#include <iostream>
#include "Logger.h"

std::mutex Logger::mutex;

void Logger::log(std::string message) const {
    std::unique_lock<std::mutex> lock(mutex);
    logModuleName();
    if(socketDescriptor != 0){
        logSocketDescriptor();
    }
    if(!message.empty()){
        logMessage(message);
    }
    logEnding();
    lock.unlock();
}

void Logger::logEnding() const { std::cout << std::endl << std::flush; }

void Logger::logMessage(const std::string &message) const { std::cout << ": " << message; }

void Logger::logModuleName() const { std::cout << moduleName; }

void Logger::logSocketDescriptor() const { std::cout << socketDescriptor; }








