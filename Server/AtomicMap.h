//
// Created by tomasz on 26.05.16.
//

#ifndef SERVER_BLOCKINGMAP_H
#define SERVER_BLOCKINGMAP_H


#include <queue>
#include <mutex>
#include <map>
#include <iostream>
#include <shared_mutex>
#include "Logger.h"


template <typename K, typename V>
class AtomicMap {
public:

    AtomicMap(std::string moduleName) : logger(moduleName) {}

    AtomicMap(const AtomicMap &) = delete;           // disable copying

    AtomicMap &operator=(const AtomicMap &) = delete; // disable assignment

    V get(K key);

    void erase(K key, V value);

    void insert(K key, V value);

    void getAllValues(std::vector<V> &values);

    void getAllKeys(std::vector<K> &values);

private:

    std::map<K, V> map;

    std::shared_timed_mutex mutex;

    Logger logger;
};


template <typename K, typename V>
V AtomicMap<K, V>::get(K key) {

    std::shared_lock<std::shared_timed_mutex> lock(mutex);
    V val = map[key];
//    log("Loaded from map");
    return val;
}

template <typename K, typename V>
void AtomicMap<K, V>::erase(K key, V value) {

    std::unique_lock<std::shared_timed_mutex> lock(mutex);
    if(*map[key] == *value) {
        map.erase(key);
        delete value;
        logger.log("Erased from map");
    }
    lock.unlock();
}

template <typename K, typename V>
void AtomicMap<K, V>::insert(K key, V value) {

    std::unique_lock<std::shared_timed_mutex> lock(mutex);
    map[key] = value;
    logger.log("Inserted into map");
    lock.unlock();
}

template <typename K, typename V>
void AtomicMap<K, V>::getAllValues(std::vector<V> &values) {

    std::shared_lock<std::shared_timed_mutex> lock(mutex);
    for(const auto &map_pairs : map) {
        values.push_back(map_pairs.second);
    }
//    log("Loaded all values");
};

template <typename K, typename V>
void AtomicMap<K, V>::getAllKeys(std::vector<K> &values) {

    std::shared_lock<std::shared_timed_mutex> lock(mutex);
    for(const auto &map_pairs : map) {
        values.push_back(map_pairs.first);
    }
//    log("Loaded all keys");
};

#endif //SERVER_BLOCKINGMAP_H
