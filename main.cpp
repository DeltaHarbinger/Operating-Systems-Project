#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "Resource.h"
#include "ProcessQueue.h"

/*!
 * This is the list of resources that the processes will be altering
 */
std::vector<Resource *> resourceList;

/*!
 * This is a tool that will generate random numbers
 */
std::default_random_engine generator(unsigned(std::chrono::steady_clock::now().time_since_epoch().count()));


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

    return 0;
}