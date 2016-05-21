//
// Created by erysman on 17.05.16.
//

#include "BlockingQueue.h"

template <typename T>
BlockingQueue<T>::BlockingQueue() {

}

template <typename T>
T BlockingQueue<T>::pop() {

    std::unique_lock<std::mutex> lock(mutex);
    while(queue.empty()){
        condition_variable.wait(lock);
    }
    auto item = queue.front();
    queue.pop();
    return item;
}

template <typename T>
void BlockingQueue<T>::pop(T &item) {

    std::unique_lock<std::mutex> lock(mutex);
    while(queue.empty()){
        condition_variable.wait(lock);
    }
    item = queue.front();
    queue.pop();
}

template <typename T>
void BlockingQueue<T>::push(const T &item) {

    std::unique_lock<std::mutex> lock(mutex);
    queue.push(item);
    lock.unlock();
    condition_variable.notify_one();
}







