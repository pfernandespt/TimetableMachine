//
// Created by paulo on 16/08/2022.
//

#ifndef UNTITLED8_LESSON_H
#define UNTITLED8_LESSON_H

#include "Time.h"
#include <string>
#include <iostream>

class Lesson {
public:
    enum Weekday {sun, mon, tue, wed, thu, fri, sat};

    Weekday weekday;
    Time beg;
    Time end;
    std::string room;

    Lesson();
    Lesson(Weekday Weekday, const Time &Beg, const Time &End, std::string& Room);
    Lesson(std::string& Weekday,std::string& Beg, std::string& End, std::string& Room);

    bool setDay(const std::string& str);

    std::string getDay() const;

    friend std::istream &operator>>(std::istream &is, Lesson &lesson);

    bool operator==(const Lesson &rhs) const;

    bool operator!=(const Lesson &rhs) const;

    bool operator<(const Lesson &rhs) const;

    bool operator>(const Lesson &rhs) const;

    bool operator<=(const Lesson &rhs) const;

    bool operator>=(const Lesson &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Lesson &lesson);



};


#endif //UNTITLED8_LESSON_H
