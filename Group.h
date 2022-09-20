//
// Created by paulo on 16/08/2022.
//

#ifndef UNTITLED8_GROUP_H
#define UNTITLED8_GROUP_H

#include <string>
#include <vector>
#include "Lesson.h"

class Group {
public:
    std::string name;
    std::vector<Lesson> schedule;

    Group() = default;
    Group(std::string &name);
    Group(std::string &name, std::vector<Lesson> &schedule);
    Group(std::string &name, Lesson& lesson);


    bool operator==(const Group &rhs) const;

    bool operator!=(const Group &rhs) const;
};


#endif //UNTITLED8_GROUP_H
