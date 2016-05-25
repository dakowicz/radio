//
// Created by erysman on 17.05.16.
//

#ifndef SERVER_BLOCKINGQUEUE_H
#define SERVER_BLOCKINGQUEUE_H

#include <queue>
#include <condition_variable>
#include <mutex>

template <typename T>
class SynchronizedStructure {
public:
    T pop();
    void get(T &item);
    void insert(const T &item);

//    SynchronizedStructure(const SynchronizedStructure&) = delete;            // disable copying
//    SynchronizedStructure& operator=(const SynchronizedStructure&) = delete; // disable assignment

private:
    T& structure;
    std::mutex mutex;
    std::condition_variable condition_variable;

    void pop(T &item);

    void push(const T &item);
};



#endif //SERVER_BLOCKINGQUEUE_H
