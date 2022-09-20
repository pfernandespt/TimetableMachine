//
// Created by paulo on 15/08/2022.
//

#ifndef UNTITLED8_RAWDATA_H
#define UNTITLED8_RAWDATA_H

#include <string>
#include <ostream>
#include "Time.h"

class RawData {
public:
    std::string subject;
    std::string group;
    std::string room;
    std::string weekday;
    Time beg;
    Time end;

    RawData(std::string data);

    bool operator<(const RawData &rhs) const;

    bool operator>(const RawData &rhs) const;

    bool operator<=(const RawData &rhs) const;

    bool operator>=(const RawData &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const RawData &data);
};


#endif //UNTITLED8_RAWDATA_H
