//
// Created by or.guz on 03-Jan-18.
//

#include "Group.h"
#define  INVALID_KEY -1 //TODO CHECK FOR DOUBLE DEFINE
Group::Group():id(INVALID_KEY) {}

Group::Group(int id) {
    if (id < 0)
        throw InvalidInput();
    this->id = id;
}

int Group::getID() const {
    return id;
}