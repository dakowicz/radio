//
// Created by tomasz on 25.05.16.
//

#ifndef SERVER_BLOCKINGQUEUE_H
#define SERVER_BLOCKINGQUEUE_H

#include "SynchronizedStructure.h"

template <typename T>
class BlockingQueue : public SynchronizedStructure<T> {
public:
    BlockingQueue();
    ~BlockingQueue();
};

BlockingQueue::BlockingQueue() {

}

BlockingQueue::~BlockingQueue() {

}


#endif //SERVER_BLOCKINGQUEUE_H
