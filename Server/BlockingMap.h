//
// Created by tomasz on 26.05.16.
//

#ifndef SERVER_BLOCKINGMAP_H
#define SERVER_BLOCKINGMAP_H


#include <queue>
#include <condition_variable>
#include <mutex>
#include <map>

template <typename K, typename V>
class BlockingMap {
public:

    BlockingMap();

    BlockingMap(const BlockingMap&) = delete;            // disable copying

    BlockingMap& operator=(const BlockingMap&) = delete; // disable assignment

    V get(K key);

    void erase(K key, V value);

    void insert(K key, V value);

private:

    std::map<K, V> map;

    std::mutex mutex;
};


template <typename K, typename V>
BlockingMap<K, V>::BlockingMap() {

}

template <typename K, typename V>
V BlockingMap<K, V>::get(K key) {

    std::unique_lock<std::mutex> lock(mutex);
    V val = map[key];
    lock.unlock();

    return val;
}

template <typename K, typename V>
void BlockingMap<K, V>::erase(K key, V value) {

    std::unique_lock<std::mutex> lock(mutex);
    if(map[key] == value) {
        map.erase(key);
    }
    lock.unlock();
}

template <typename K, typename V>
void BlockingMap<K, V>::insert(K key, V value) {

    std::unique_lock<std::mutex> lock(mutex);
    map[key] = value;
    lock.unlock();
}


#endif //SERVER_BLOCKINGMAP_H
