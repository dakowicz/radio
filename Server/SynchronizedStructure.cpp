//
// Created by erysman on 17.05.16.
//

#include "SynchronizedStructure.h"

template <typename T>
T SynchronizedStructure<T>::pop() {

    std::unique_lock<std::mutex> lock(mutex);
    while(structure.empty()){
        condition_variable.wait(lock);
    }
    auto item = structure.front();
    structure.pop();
    return item;
}

template <typename T>
void SynchronizedStructure<T>::pop(T &item) {

    std::unique_lock<std::mutex> lock(mutex);
    while(structure.empty()){
        condition_variable.wait(lock);
    }
    item = structure.front();
    structure.pop();
}

template <typename T>
void SynchronizedStructure<T>::push(const T &item) {

    std::unique_lock<std::mutex> lock(mutex);
    structure.push(item);
    lock.unlock();
    condition_variable.notify_one();
}
