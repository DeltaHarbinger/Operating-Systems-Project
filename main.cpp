#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
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
 * List of all processes completed processes
 */
 std::vector<Process *> completedProcesses;

/*!
 * Lock that states whether or not the list is locked from searchong,
 * adding or deleting
 */
//bool listLock;

/*!
 * These are process pointers that represent the active processes in
 * the processor.
 */
Process * processorA; //FIFO
Process * processorB; //Round Robin

/*!
 * This is a tool that will generate random numbers
 */
std::default_random_engine generator(unsigned(std::chrono::steady_clock::now().time_since_epoch().count()));

/*!
 * Number of seconds since system started processing processes
 */
unsigned int systemTime = 0;

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
            completedProcesses.push_back(processorA);
            processorA = nullptr;
        }
    }
    if(processorB != nullptr){
        processorB -> reduceRemainingTime(1);
        if(processorB -> getRemainingTime() == 0){
            completedProcesses.push_back(processorB);
            processorB = nullptr;
        }
    }
}

void assignProcesses(){

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



/*!
 * This function will return a random integer. (within the valid range of integers)
 */
int generateRandomNumber(){
    return generator();
}

/*!  This is the function that tells the sorter
 *  how to sort the list. If you have two resources,
 *  if the value of resource 'a' is smaller than
 *  the value of resource 'b', resource a comes
 *  first
 */
bool sortCondition(Resource * a, Resource * b){
    return a -> getValue() < b -> getValue();
}

bool sortStartOrder(Process * a, Process * b){
    return a -> getStartTime() < b -> getEndTime();
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
        std::cout << (resourceList.size()) << std::endl;
        key = generateRandomNumber();
    }
    resourceList.push_back(new Resource(key, value));
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
 * This function will sort the resource list in ascending
 * order by resource value.
 */
void sortList(){
    std::sort(resourceList.begin(), resourceList.end(), sortCondition);
}

/*!
 * This function will return the sum of all of the values in the list
 */
long listTotal(){
    long total = 0;
    for(Resource * r : resourceList){
        total += r -> getValue();
    }
    return total;
}

/*!
 * Main function
 */
int main() {

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

        int endTime;
        endTime = getNumber("Enter the time that the process is to start");
        while(endTime < 0){
            endTime = getNumber("PLEASE ENTER A VALID VALUE\nEnter the time that the process is to start");
        }

        if(startTime >= endTime){
            std::cout << "INVALID START AND END TIME ENTERED" << std::endl;
            system("pause");
            continue;
        }

        int remainingTime = endTime - startTime;

        Process * p = new Process(processId, task, 0, startTime, endTime, remainingTime, 0, 0);

        processes.push_back(p);

        processId++;

        if(processId >= 9){
            char option = 0;
            while(option != 'y' && option != 'n'){
                system("cls");
                std::cout << "Keep entering? (y/n)" << std::endl;
                std::cin >> option;
            }
            keepEntering = option == 'y';
        }
    }

    std::sort(processes.begin(), processes.end(), sortStartOrder);

    return 0;
}