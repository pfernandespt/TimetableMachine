//
// Created by paulo on 16/08/2022.
//

#include "Group.h"

Group::Group(std::string &name) : name(name) {}

bool Group::operator==(const Group &rhs) const {
    return name == rhs.name;
}

bool Group::operator!=(const Group &rhs) const {
    return !(rhs == *this);
}

Group::Group(std::string &name,std::vector<Lesson> &schedule) : name(name), schedule(schedule) {}

Group::Group(std::string &name, Lesson& lesson) : name(name) {
    schedule.push_back(lesson);
}
