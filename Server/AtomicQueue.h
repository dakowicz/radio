//
// Created by erysman on 17.05.16.
//

#ifndef SERVER_BLOCKINGQUEUE_H
#define SERVER_BLOCKINGQUEUE_H

#include <queue>
#include <condition_variable>
#include <mutex>
#include <iostream>

template <typename T>
class AtomicQueue {
public:

    AtomicQueue();

    AtomicQueue(std::string &moduleName);

    AtomicQueue(const AtomicQueue &) = delete;           // disable copying

    AtomicQueue &operator=(const AtomicQueue &) = delete; // disable assignment

    ~AtomicQueue();

    T pop();

    void push(const T &item);

    void pop(T &item);

private:

    std::queue<T> queue;

    std::mutex mutex;

    std::condition_variable condition_variable;

    std::string moduleName;

    void log(std::string message);
};


template <typename T>
AtomicQueue<T>::AtomicQueue(std::string &moduleName) {
    this->moduleName = moduleName;
}

template <typename T>
AtomicQueue<T>::AtomicQueue() {

}

template <typename T>
AtomicQueue<T>::~AtomicQueue() {

}

template <typename T>
T AtomicQueue<T>::pop() {

    std::unique_lock<std::mutex> lock(mutex);
    while(queue.empty()) {
        condition_variable.wait(lock);
    }
    auto item = queue.front();
    log("Popped message from queue");
    queue.pop();
    return item;
}

template <typename T>
void AtomicQueue<T>::pop(T& item) {

    std::unique_lock<std::mutex> lock(mutex);
    while(queue.empty()) {
        condition_variable.wait(lock);
    }
    item = queue.front();
    log("Popped message from queue");
    queue.pop();
}

template <typename T>
void AtomicQueue<T>::push(const T &item) {

    std::unique_lock<std::mutex> lock(mutex);
    queue.push(item);
    log("Pushed message to queue");
    lock.unlock();
    condition_variable.notify_one();
}

template <typename T>
void AtomicQueue<T>::log(std::string message) {
    std::cout << this->moduleName << ": " <<  message << std::endl << std::flush;
}


#endif //SERVER_BLOCKINGQUEUE_H