//
// Created by Brandon Chung on 10/31/2018.
//

#ifndef OPERATINGSYSTEMSPROJECT_PROCESSNODE_H
#define OPERATINGSYSTEMSPROJECT_PROCESSNODE_H

#include "Process.h"

class ProcessNode {
private:
    Process * data;
    ProcessNode * previousNode;
    ProcessNode * nextNode;

public:
    ProcessNode(Process *data, ProcessNode *previousNode, ProcessNode *nextNode) : data(data),
                                                                                   previousNode(previousNode),
                                                                                   nextNode(nextNode) {}

    Process *getData() const {
        return data;
    }

    void setData(Process *data) {
        ProcessNode::data = data;
    }

    ProcessNode *getPreviousNode() const {
        return previousNode;
    }

    void setPreviousNode(ProcessNode *previousNode) {
        ProcessNode::previousNode = previousNode;
    }

    ProcessNode *getNextNode() const {
        return nextNode;
    }

    void setNextNode(ProcessNode *nextNode) {
        ProcessNode::nextNode = nextNode;
    }
};


#endif //OPERATINGSYSTEMSPROJECT_PROCESSNODE_H
