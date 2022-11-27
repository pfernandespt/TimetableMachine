//
// Created by paulo on 16/08/2022.
//

#include "Lesson.h"

#include <utility>

Lesson::Lesson(){
    weekday = sun;
    beg.setTime(0,0,0);
    end.setTime(0,0,0);
}


Lesson::Lesson(std::string& Weekday,std::string& Beg,std::string& End, std::string& Room) : room(Room) {
    setDay(Weekday);
    beg.setTime(Beg);
    end.setTime(End);
}

Lesson::Lesson(Lesson::Weekday Weekday, const Time &Beg, const Time &End, std::string& Room) : weekday(Weekday), beg(Beg), end(End) , room(Room) {}

bool Lesson::setDay(const std::string& str) {
    if(str.find("Dom") != std::string::npos){
        weekday = sun;
    }else if(str.find("Seg") != std::string::npos){
        weekday = mon;
    }else if(str.find("Ter") != std::string::npos){
        weekday = tue;
    }else if(str.find("Qua") != std::string::npos){
        weekday = wed;
    }else if(str.find("Qui") != std::string::npos) {
        weekday = thu;
    }else if(str.find("Sex") != std::string::npos) {
        weekday = fri;
    }else if(str.find("ado") != std::string::npos){
        weekday = sat;
    }else return false;

    return true;
}

std::string Lesson::getDay() const{
    switch(weekday){
        case sun:
            return "Dom";
        case mon:
            return "Seg";
        case tue:
            return "Ter";
        case wed:
            return "Qua";
        case thu:
            return "Qui";
        case fri:
            return "Sex";
        case sat:
            return "Sab";
        default:
            return "Meke";
    }
}

std::istream &operator>>(std::istream &is, Lesson &lesson) {
    std::string Weekday, Beg, End;
    std::getline(is, lesson.room, ';');
    std::getline(is, Weekday, ';');
    std::getline(is, Beg, ';');
    std::getline(is, End);

    lesson.setDay(Weekday);
    lesson.beg = Time(Beg);
    lesson.end = Time(End);

    return is;
}

bool Lesson::operator==(const Lesson &rhs) const {
    return weekday == rhs.weekday &&
           beg == rhs.beg &&
           end == rhs.end;
}

bool Lesson::operator!=(const Lesson &rhs) const {
    return !(rhs == *this);
}

bool Lesson::operator<(const Lesson &rhs) const {
    if (weekday < rhs.weekday)
        return true;
    if (rhs.weekday < weekday)
        return false;
    return beg < rhs.beg;
}

bool Lesson::operator>(const Lesson &rhs) const {
    return rhs < *this;
}

bool Lesson::operator<=(const Lesson &rhs) const {
    return !(rhs < *this);
}

bool Lesson::operator>=(const Lesson &rhs) const {
    return !(*this < rhs);
}

std::ostream &operator<<(std::ostream &os, const Lesson &lesson) {
    os << lesson.room << ';' << lesson.getDay() << ';' << lesson.beg << ';' << lesson.end;
    return os;
}
