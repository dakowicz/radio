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
#include "../../../logger/Logger.h"
#include "../../dispatcher/domain/Data.h"


template <typename K, typename V>
class ClientsMap {
public:

    ClientsMap(std::string moduleName) : logger(moduleName) {}

    ClientsMap(const ClientsMap &) = delete;           // disable copying

    ClientsMap &operator=(const ClientsMap &) = delete; // disable assignment

    V get(K key);

    void erase(K key, V value);

    void insert(K key, V value);

    void getAllValues(std::vector<V> &values);

    void getAllKeys(std::vector<K> &values);

    void broadcast(std::shared_ptr<Data> data);

private:

    std::map<K, V> map;

    std::shared_timed_mutex mutex;

    Logger logger;

};


template <typename K, typename V>
V ClientsMap<K, V>::get(K key) {

    std::shared_lock<std::shared_timed_mutex> lock(mutex);
    V val = map[key];
//    log("Loaded from map");
    return val;
}

template <typename K, typename V>
void ClientsMap<K, V>::erase(K key, V value) {

    std::unique_lock<std::shared_timed_mutex> lock(mutex);
    if(*map[key] == *value) {
        map.erase(key);
        delete value;
        logger.log("Erased from map");
    }
    lock.unlock();
}

template <typename K, typename V>
void ClientsMap<K, V>::insert(K key, V value) {

    std::unique_lock<std::shared_timed_mutex> lock(mutex);
    map[key] = value;
    logger.log("Inserted into map");
    lock.unlock();
}

template <typename K, typename V>
void ClientsMap<K, V>::getAllValues(std::vector<V> &values) {

    std::shared_lock<std::shared_timed_mutex> lock(mutex);
    for(const auto &map_pairs : map) {
        values.push_back(map_pairs.second);
    }
//    log("Loaded all values");
};

template <typename K, typename V>
void ClientsMap<K, V>::getAllKeys(std::vector<K> &values) {

    std::shared_lock<std::shared_timed_mutex> lock(mutex);
    for(const auto &mapPair : map) {
        values.push_back(mapPair.first);
    }
//    log("Loaded all keys");
}

template <typename K, typename V>
void ClientsMap<K, V>::broadcast(std::shared_ptr<Data> data) {

    std::shared_lock<std::shared_timed_mutex> lock(mutex);
    for(const auto &mapPair : map) {
        mapPair.second->send(data);
    }
};

#endif //SERVER_BLOCKINGMAP_H
