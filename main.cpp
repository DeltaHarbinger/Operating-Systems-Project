#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream>
#include "Resource.h"
#include "ProcessQueue.h"

/*!
 * This is the list of resources that the processes will be altering
 */
std::vector<Resource *> resourceList;

/*!
 * List of all processes that will act on the list of resources
 */
std::vector<Process *> processes;

/*!
 * This is the queue that stores the next 5 processes available to run
 */
std::vector<Process *> readyQueue;

/*!
 * List of all processes completed processes
 */
 std::vector<Process *> completedProcesses;

/*!
 * Lock that states whether or not the list is locked from searching,
 * adding or deleting
 */


/*!
 * These are process pointers that represent the active processes in
 * the processor.
 */
Process * processorA = nullptr; //FIFO
Process * processorB = nullptr; //Round Robin

/*!
 * This is a tool that will generate random numbers
 */
std::default_random_engine generator(unsigned(std::chrono::steady_clock::now().time_since_epoch().count()));

/*!
 * Number of seconds since system started processing processes
 */
unsigned int systemTime = 0;

/*!
 * This function will return a random integer. (within the valid range of integers)
 */
int generateRandomNumber(){
    return generator();
}

/*!
 * This function will search the list for a key
 */
Resource * searchList(int key){
    if(resourceList.empty()){
        return nullptr;
    }
    bool found = false;
    int i = 0;
    while(i < resourceList.size() && !found){
        if(resourceList[i] -> getKey() == key){
            found = true;
        }
        i++;
    }
    if(found){
        return resourceList[i - 1];
    } else {
        return nullptr;
    }
}

/*!
 * This is a function that inserts a new resource
 * into the list when given the value of the resource.
 */
void insertValue(int value){
    int key = generateRandomNumber();
    while(searchList(key) != nullptr){
        key = generateRandomNumber();
    }
    resourceList.push_back(new Resource(key, value));
}

/*!  This is the function that tells the sorter
 *  how to sort the list. If you have two resources,
 *  if the value of resource 'a' is smaller than
 *  the value of resource 'b', resource a comes
 *  first
 */
bool sortResourceCondition(Resource *a, Resource *b){
    return a -> getValue() < b -> getValue();
}

/*!
 * This function will sort the resource list in ascending
 * order by resource value.
 */
void sortList(){
    std::sort(resourceList.begin(), resourceList.end(), sortResourceCondition);
}

/*!
 * This is a function that removes a resource from the
 * resource list. It takes the key of the resource to
 * be removed, searches for it and deletes it if found.
 */
bool removeValue(int key){
    if(resourceList.empty()){
        return false;
    }
    bool found = false;
    int i = 0;
    while(i < resourceList.size() && !found){
        if(resourceList[i] -> getKey() == key){
            found = true;
        }
        i++;
    }
    if(found){
        resourceList.erase(resourceList.begin() + i - 1);
        return true;
    } else {
        return false;
    }
}

/*!
 * This function will return the sum of all of the values in the list
 */
long long listTotal(){
    long long total = 0;
    for(Resource * r : resourceList){
        total += r -> getValue();
    }
    return total;
}

/*!
 * Performs the task of a specified process on the list
 */
void performAction(Process * p){
    switch(p -> getTask()){
        case 1: {
            insertValue(generateRandomNumber());
            std::cout << "Inserted value" << std::endl;
            break;
        }
        case 2: {
            int keyToRemove;
            if (resourceList.size() > 0) {
                keyToRemove = generateRandomNumber() % resourceList.size();
            } else {
                keyToRemove = 0;
            }
            bool success = removeValue(resourceList[keyToRemove]->getKey());
            std::cout << (success ? "Key removed" : "Key not removed") << std::endl;
            break;
        }
        case 3: {
            sortList();
            std::cout << "Sorted" << std::endl;
            break;
        }
        case 4: {
            int keyToSearch;
            if(resourceList.size() > 0){
                keyToSearch = generateRandomNumber() % resourceList.size();
            } else {
                keyToSearch = 0;
            }
            Resource * result = searchList(keyToSearch);
            if(result != nullptr){
                std::cout << result -> getValue() << std::endl;
            } else {
                std::cout << "Value not found" << std::endl;
            }
            break;
        }
        case 5: {
            long long total = listTotal();
            std::cout << "The total is: " << total << std::endl;
        }
    }
}

/*!
 * Function that advances the "system" by one quantum, reduces
 * the remaining time of active processes and moves finished processes
 * to a list of completed processes
 */
void systemClockTick(){
    systemTime += 1;
    if(processorA != nullptr){
        processorA -> reduceRemainingTime(1);
        if(processorA -> getRemainingTime() == 0){
            performAction(processorA);
            processorA -> setEndTime(systemTime);
            completedProcesses.push_back(processorA);
            processorA = nullptr;
        }
    }
    if(processorB != nullptr){
        processorB -> reduceRemainingTime(1);
        if(processorB -> getRemainingTime() == 0){
            performAction(processorB);
            processorB -> setEndTime(systemTime);
            completedProcesses.push_back(processorB);
            processorB = nullptr;
        }
    }
}

void loadReadyQueue(){
    bool processesAvailable = true;
    int assignedProcessCount = 0;
    if(processorA != nullptr){
        assignedProcessCount += 1;
    }
    if(processorB != nullptr){
        assignedProcessCount += 1;
    }
    while(processesAvailable && readyQueue.size() < 5 - assignedProcessCount && processes.size() > 0){
        if(processes[0] -> getStartTime() <= systemTime){
            readyQueue.push_back(processes[0]);
            processes.erase(processes.begin());
        } else {
            processesAvailable = false;
        }
    }
}

int getOldestProcess(){
    int oldestProcess = 0;
    bool found = false;
    for(int i = 0; i < readyQueue.size(); i++){
        found = true;
        if(readyQueue[i] -> getTask() < 4 &&  readyQueue[oldestProcess] -> getTask() > 3){
            oldestProcess = i;
        }
        if(readyQueue[i] -> getStartTime() < readyQueue[oldestProcess] -> getStartTime()){
            if(readyQueue[oldestProcess] -> getTask() < 4){
                if(readyQueue[i] -> getTask() < 4){
                    oldestProcess = i;
                }
            } else {
                oldestProcess = i;
            }
        }
    }
    return found ? oldestProcess : -1;
}

int getOldestNonPriorityProcess(){
    int oldestNonPriorityProcess = -1;
    bool found = false;
    for(int x = 0; x < readyQueue.size(); x++){
        if(oldestNonPriorityProcess == -1 && readyQueue[x] -> getTask() > 3){
            oldestNonPriorityProcess = x;
        } else {
            if(readyQueue[x] -> getTask() > 3 && readyQueue[x] -> getStartTime() < readyQueue[oldestNonPriorityProcess] -> getStartTime()){
                oldestNonPriorityProcess = x;
            }
        }
    }
    return found ? oldestNonPriorityProcess : -1;
}

/*!
 * Assigns processes in the ready queue to processors based on priority and order of arrival
 */
void assignProcesses(){
    loadReadyQueue();
    int processToAssign = getOldestProcess();
    if(readyQueue.size() > 0){
        if(processorA == nullptr && processorB == nullptr) {
            processorA = readyQueue[processToAssign];
            readyQueue.erase(readyQueue.begin() + processToAssign);
            processorA -> addAttempt();
            if (processorA->getTask() > 3) {
                int nextProcessToAssign = getOldestProcess();
                if(nextProcessToAssign != -1){
                    processorB = readyQueue[nextProcessToAssign];
                    processorB -> addAttempt();
                    readyQueue.erase(readyQueue.begin() + nextProcessToAssign);
                }
            }
        }
        if(processorA != nullptr && processorB == nullptr){
            if(processorA -> getTask() > 3){
                if(processorB == nullptr){
                    int nextProcessToAssign = getOldestNonPriorityProcess();
                    if(nextProcessToAssign != -1){
                        processorB = readyQueue[processToAssign];
                        processorB -> addAttempt();
                        readyQueue.erase(readyQueue.begin() + nextProcessToAssign);
                    }
                }
            }
        }
        if(processorA == nullptr && processorB != nullptr){
            if(processorB -> getTask() > 3){
                processToAssign = getOldestNonPriorityProcess();
                if(processToAssign != -1){
                    processorA = readyQueue[processToAssign];
                    processorA -> addAttempt();
                    readyQueue.erase(readyQueue.begin() + processToAssign);
                } else {
                    readyQueue.push_back(processorB);
                    processorB = readyQueue[processToAssign];
                    processorA -> addAttempt();
                    readyQueue.erase(readyQueue.begin() + processToAssign);
                }
            }
        }
//        if(processorA != nullptr && processorB != nullptr){
//            if(processorA -> getTask() > 3){
//                if(readyQueue[processToAssign] -> getTask() <= 3){
//
//                }
//            }
//        }


//        } else {
//            if(processorA -> getTask() > 3){
//                if(processorB == nullptr){
//                    if(readyQueue[processToAssign] -> getTask() > 3){
//                        processorB = readyQueue[processToAssign];
//                        readyQueue.erase(readyQueue.begin() + processToAssign);
//                    } else {
//                        readyQueue.push_back(processorA);
//                        processorA -> addAttempt();
//                        processorA = readyQueue[processToAssign];
//                        readyQueue.erase(readyQueue.begin() + processToAssign);
//                    }
//                }
//            }
//
//        }

    }
}

/*!
 * Checks if a string has no tabs or spaces
 */
bool stringSafe(std::string s){
    bool valid = true;
    for(int x = 0; x < s.size() && valid; x++){
        s[x] != '\t' ? false : valid = false;
    }
    return valid;
}

/*!
 * Checks if a string only has letters
 */
bool stringOnlyHasLetters(std::string s){
    bool valid = true;
    if(s == ""){
        return false;
    }
    for(int x = 0; x < s.size() && valid; x++){
        isalpha(s[x]) ? false : valid = false;
    }
    return valid;
}

/*!
 * Gets a string from the user. The string can be safe (no spaces or tabs)
 * or it can be strics (only letters)
 */
std::string getString(std::string message, bool strict){
    system("cls");
    std::string input = "";
    std::cout << message << std::endl << (strict ? ">> " : "> ");
    std::cin.sync();
    getline(std::cin, input);
    if(input == ""){
        input = "NA";
    }
    while(strict && !stringOnlyHasLetters(input)){
        std::cout << std::endl << message << std::endl << "(Letters are the only accepted text here)" << std::endl << "> ";
        std::cin.sync();
        getline(std::cin, input);
    }
    while(!strict && !stringSafe(input)){
        std::cout << message << std::endl << (strict ? ">> " : "> ");
        std::cin.sync();
        getline(std::cin, input);
    }
    return input;
}

/*!
 * makes the user enter a number. It will make the user start over if
 * an invalid input is given
 */
int getNumber(std::string message){
    system("cls");
    std::cout << message << std::endl << "# ";
    int number;
    std::cin >> number;
    while(!std::cin){
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cout << std::endl << message << std::endl << "Please enter a valid value" << std::endl << "# ";
        std::cin >> number;
    }
    return number;
}





/*!  This is the function that tells the sorter
 *  how to sort the processes. If you have two
 *  processes, if the start time of process'a' is smaller than
 *  the start time of process 'b', process a comes
 *  first
 */
bool sortStartOrder(Process * a, Process * b){
    return a -> getStartTime() < b -> getEndTime();
}


void getProcesses(){
    bool keepEntering = true;

    int processId = 0;

    while(keepEntering && processId < 30){

        int task = getNumber("Enter the task you want to perform\n1) Add\n2)Remove\n3)Sort\n4)Search\n5)Total");
        while(task > 5 || task < 1){
            task = getNumber("PLEASE ENTER A VALID VALUE\nEnter the task you want to perform\n1) Add\n2)Remove\n3)Sort\n4)Search\n5)Total");
        }


        int startTime;
        startTime = getNumber("Enter the time that the process is to start");
        while(startTime < 0){
            startTime = getNumber("PLEASE ENTER A VALID VALUE\nEnter the time that the process is to start");
        }

        int duration;
        duration = getNumber("Enter the duration of the process");
        while(duration < 0){
            duration = getNumber("PLEASE ENTER A VALID VALUE\nEnter the time that the process is to start");
        }


        Process * p = new Process(processId, task, 0, startTime, 0, duration, 0, 0);

        processes.push_back(p);

        processId++;

        if(processId > 9){
            char option = 0;
            while(option != 'y' && option != 'n'){
                system("cls");
                std::cout << "Keep entering? (y/n)" << std::endl;
                std::cin >> option;
            }
            keepEntering = option == 'y';
        }
    }
}

/*!
 * Main function
 */
int main() {

    getProcesses();

    std::sort(processes.begin(), processes.end(), sortStartOrder);

    while(readyQueue.size() > 0 || processes.size() > 0 || processorA != nullptr || processorB != nullptr){
        assignProcesses();
        systemClockTick();
    }

    std::string report = "";

    for(Process * p : completedProcesses){
        report = report +  (p -> toString()) + "\n";
    }

    std::cout << report;

    std::ofstream fileWriter;
    fileWriter.open("report.txt");
    fileWriter << report;
    fileWriter.close();

    return 0;
}