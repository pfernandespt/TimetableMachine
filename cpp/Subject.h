//
// Created by paulo on 16/08/2022.
//

#ifndef UNTITLED8_SUBJECT_H
#define UNTITLED8_SUBJECT_H

#include <string>
#include <vector>
#include "Group.h"

class Subject {
public:
    std::string abbreviation;
    std::string type;
    bool enabled;
    std::vector<Group> groups;

    Subject();

    Subject(const std::string &abbreviation, const std::string &type);

    bool operator==(const Subject &rhs) const;

    bool operator!=(const Subject &rhs) const;
};


#endif //UNTITLED8_SUBJECT_H
