//
// Created by Brandon Chung on 10/31/2018.
//

#ifndef OPERATINGSYSTEMSPROJECT_PROCESSQUEUE_H
#define OPERATINGSYSTEMSPROJECT_PROCESSQUEUE_H

#include "ProcessNode.h"

class ProcessQueue {
private:
    ProcessNode * front;
    ProcessNode * rear;
public:

    ProcessQueue(ProcessNode *front, ProcessNode *rear) : front(front), rear(rear) {}

    ProcessNode *getFront() const {
        return front;
    }

    void setFront(ProcessNode *front) {
        ProcessQueue::front = front;
    }

    ProcessNode *getRear() const {
        return rear;
    }

    void setRear(ProcessNode *rear) {
        ProcessQueue::rear = rear;
    }

    
};


#endif //OPERATINGSYSTEMSPROJECT_PROCESSQUEUE_H
