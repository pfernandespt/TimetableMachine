//
// Created by paulo on 15/08/2022.
//

#include "RawData.h"

RawData::RawData(std::string data) {
    unsigned long long first, second;

    //otimizar leitura com os finds e rfinds baseados em start/ end pos !!!
    first = data.find('\"') + 1;
    second = data.find(' ');
    weekday = data.substr(first, second - first);

    first = second + 1;
    second = data.find('-');
    beg = Time(data.substr(first, second - first));

    first = second + 1;
    second = data.find("\" ");
    end = Time(data.substr(first, second - first));

    first = data.find("<span>") + 6;
    second = data.find("</span");
    subject = data.substr(first, second - first);

    second =  data.find("</c></span></salas>");
    first = data.rfind("<c>", second) + 3;
    room = data.substr(first, second - first);

    first = data.find("</salas><span><c>") + 17;
    second = data.find("</c>", first);
    group = data.substr(first, second - first);
}



std::ostream &operator<<(std::ostream &os, const RawData &data) {
    os << data.subject << ';' << data.group << ';' << data.room <<  ';'
       << data.weekday << ';' << data.beg << ';'<< data.end;
    return os;
}

bool RawData::operator<(const RawData &rhs) const {
    if (subject < rhs.subject)
        return true;
    if (rhs.subject < subject)
        return false;
    if (group < rhs.group)
        return true;
    if (rhs.group < group)
        return false;
    if (weekday < rhs.weekday)
        return true;
    if (rhs.weekday < weekday)
        return false;
    return beg < rhs.beg;
}

bool RawData::operator>(const RawData &rhs) const {
    return rhs < *this;
}

bool RawData::operator<=(const RawData &rhs) const {
    return !(rhs < *this);
}

bool RawData::operator>=(const RawData &rhs) const {
    return !(*this < rhs);
}


