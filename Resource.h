//
// Created by Brandon Chung on 11/2/2018.
//

#ifndef OPERATINGSYSTEMSPROJECT_RESOURCE_H
#define OPERATINGSYSTEMSPROJECT_RESOURCE_H


class Resource {
private:
    int key;
    int value;

public:
    Resource(int key, int value) : key(key), value(value) {}

    int getKey() const {
        return key;
    }

    void setKey(int key) {
        Resource::key = key;
    }

    int getValue() const {
        return value;
    }

    void setValue(int value) {
        Resource::value = value;
    }
};


#endif //OPERATINGSYSTEMSPROJECT_RESOURCE_H
