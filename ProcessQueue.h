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

    ProcessQueue() {
        this -> front = nullptr;
        this -> rear = nullptr;
    }

    void enqueue(Process * p){
        ProcessNode * temp = new ProcessNode(p, rear, nullptr);
        if(front == nullptr){
            front = temp;
            rear = temp;
        } else {
            rear -> setNextNode(temp);
            rear = temp;
        }
    }

    void dequeue(){
        if(front != nullptr){
            ProcessNode * temp = front;
            if(front == rear){
                front = nullptr;
                rear = nullptr;
                delete temp;
            } else {
                front = front -> getNextNode();
                delete temp;
            }
        } else {
            throw 1; //Exception of 1 means the queue was empty
        }
    }

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

    bool isEmpty(){
        return front == nullptr;
    }


};


#endif //OPERATINGSYSTEMSPROJECT_PROCESSQUEUE_H
