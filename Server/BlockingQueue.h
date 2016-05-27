//
// Created by erysman on 17.05.16.
//

#ifndef SERVER_BLOCKINGQUEUE_H
#define SERVER_BLOCKINGQUEUE_H

#include <queue>
#include <condition_variable>
#include <mutex>

template <typename T>
class BlockingQueue {
public:

    BlockingQueue();

    BlockingQueue& operator=(const BlockingQueue&) = delete; // disable assignment

    BlockingQueue(const BlockingQueue&) = delete;            // disable copying

    BlockingQueue(std::string *moduleName);

    ~BlockingQueue();

    T pop();

    void pop(T& item);

    void push(const T& item);

private:

    void log(const char *message);

    std::queue<T> queue;

    std::mutex mutex;

    std::condition_variable condition_variable;

    std::string *moduleName;
};


template <typename T>
BlockingQueue<T>::BlockingQueue(std::string *moduleName) {
    this->moduleName = moduleName;
}

template <typename T>
BlockingQueue<T>::BlockingQueue() {

}

template <typename T>
BlockingQueue<T>::~BlockingQueue() {

}

template <typename T>
T BlockingQueue<T>::pop() {

    std::unique_lock<std::mutex> lock(mutex);
    while(queue.empty()) {
        condition_variable.wait(lock);
    }
    auto item = queue.front();
    queue.pop();
    return item;
}

template <typename T>
void BlockingQueue<T>::pop(T &item) {

    std::unique_lock<std::mutex> lock(mutex);
    while(queue.empty()) {
        condition_variable.wait(lock);
    }
    item = queue.front();
    queue.pop();
}

template <typename T>
void BlockingQueue<T>::push(const T &item) {

    std::unique_lock<std::mutex> lock(mutex);
    queue.push(item);
    log("Pushed message to the message queue");
    lock.unlock();
    condition_variable.notify_one();
}

void BlockingQueue::log(const char *message) {
    if(moduleName != nullptr) {

    }
}


#endif //SERVER_BLOCKINGQUEUE_H