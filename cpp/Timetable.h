//
// Created by paulo on 18/08/2022.
//

#ifndef UNTITLED8_TIMETABLE_H
#define UNTITLED8_TIMETABLE_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "Time.h"
#include "Subject.h"

class Timetable {
public:
    std::string name;
    std::map<Time, Time> occ [7];
    std::multimap<std::string, Group> subjects;

    Timetable();
    Timetable(std::string Name);


    void resetTimetable();
    bool isCompatible(const Lesson& l) const;
    bool isCompatible(const Group& g) const;
    bool addGroup(const std::string& subject_abbrev, Group & group);

    void exportTimetable(const std::string& filename) const;
    void exportHtmlTimetable(const std::string& filename) const;


};


#endif //UNTITLED8_TIMETABLE_H
