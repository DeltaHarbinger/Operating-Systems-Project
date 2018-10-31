//
// Created by Brandon Chung on 10/31/2018.
//

#ifndef OPERATINGSYSTEMSPROJECT_PROCESS_H
#define OPERATINGSYSTEMSPROJECT_PROCESS_H

#include <chrono>
#include <string>
class Process {
private:
    int processId;
    int task;
    int baseAddress;
    std::chrono::time_point<std::chrono::system_clock> startTime;
    std::chrono::time_point<std::chrono::system_clock> endTime;
    int attempts;
    int sleepTime;

public:
    Process(int processId, int task, int baseAddress,
            const std::chrono::time_point<std::chrono::system_clock> &startTime,
            const std::chrono::time_point<std::chrono::system_clock> &endTime, int attempts, int sleepTime) : processId(
            processId), task(task), baseAddress(baseAddress), startTime(startTime), endTime(endTime), attempts(
            attempts), sleepTime(sleepTime) {}

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

    const std::chrono::time_point<std::chrono::system_clock> &getStartTime() const {
        return startTime;
    }

    void setStartTime(const std::chrono::time_point<std::chrono::system_clock> &startTime) {
        Process::startTime = startTime;
    }

    const std::chrono::time_point<std::chrono::system_clock> &getEndTime() const {
        return endTime;
    }

    void setEndTime(const std::chrono::time_point<std::chrono::system_clock> &endTime) {
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
