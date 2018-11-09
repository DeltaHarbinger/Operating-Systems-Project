//
// Created by Brandon Chung on 10/31/2018.
//

#ifndef OPERATINGSYSTEMSPROJECT_PROCESS_H
#define OPERATINGSYSTEMSPROJECT_PROCESS_H

#include <string>
class Process {
private:
    int processId;
    int task; // 1: Add, 2: Remove, 3: Sort, 4: Retrieve, 5: List Total
    int baseAddress;
    int startTime;
    int endTime;
    int remainingTime;
    int attempts;
    int sleepTime;

public:
    Process(int processId, int task, int baseAddress, int startTime, int endTime, int remainingTime, int attempts,
            int sleepTime) : processId(processId), task(task), baseAddress(baseAddress), startTime(startTime),
                             endTime(endTime), remainingTime(remainingTime), attempts(attempts), sleepTime(sleepTime) {}

    Process() {
        this -> processId = 0;
        this -> task = 0;
        this -> baseAddress = 0;
        this -> startTime = 0;
        this -> endTime = 0;
        this -> remainingTime = 0;
        this -> attempts = 0;
        this -> sleepTime = 0;
    }

    int getProcessId() const {
        return processId;
    }

    void setProcessId(int processId) {
        Process::processId = processId;
    }

    int getTask() const {
        return task;
    }

    void setTask(int task) {
        Process::task = task;
    }

    int getBaseAddress() const {
        return baseAddress;
    }

    void setBaseAddress(int baseAddress) {
        Process::baseAddress = baseAddress;
    }

    int getStartTime() const {
        return startTime;
    }

    void setStartTime(int startTime) {
        Process::startTime = startTime;
    }

    int getEndTime() const {
        return endTime;
    }

    void setEndTime(int endTime) {
        Process::endTime = endTime;
    }

    int getAttempts() const {
        return attempts;
    }

    void setAttempts(int attempts) {
        Process::attempts = attempts;
    }

    int getSleepTime() const {
        return sleepTime;
    }

    void setSleepTime(int sleepTime) {
        Process::sleepTime = sleepTime;
    }

};


#endif //OPERATINGSYSTEMSPROJECT_PROCESS_H
