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
    T pop();
    void pop(T& item);
    void push(const T& item);

    BlockingQueue(const BlockingQueue&) = delete;            // disable copying
    BlockingQueue& operator=(const BlockingQueue&) = delete; // disable assignment

private:
    std::queue<T> queue;
    std::mutex mutex;
    std::condition_variable condition_variable;
};



#endif //SERVER_BLOCKINGQUEUE_H
