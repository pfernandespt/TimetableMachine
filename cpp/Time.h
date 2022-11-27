//
// Created by paulo on 14/08/2022.
//

#ifndef UNTITLED8_TIME_H
#define UNTITLED8_TIME_H

#include <string>
#include <iostream>
#include <iomanip>

#define TIME_STRING_CHARS "0123456789:"

class Time {
private:
    unsigned hours_;
    unsigned minutes_;
    unsigned seconds_;
public:
    Time();
    Time(unsigned int hours, unsigned int minutes, unsigned int seconds);
    Time(std::string str);
    Time(unsigned seconds);


    unsigned int getHours() const;
    unsigned int getMinutes() const;
    unsigned int getSeconds() const;
    std::string getTime() const;

    unsigned int inSeconds() const;
    static unsigned int inSeconds(const Time& t);

    void setTime(unsigned seconds);
    void setTime(unsigned hours, unsigned minutes, unsigned seconds);
    bool setTime(std::string str);

    bool operator==(const Time &rhs) const;
    bool operator!=(const Time &rhs) const;

    bool operator<(const Time &rhs) const;

    bool operator>(const Time &rhs) const;

    bool operator<=(const Time &rhs) const;

    bool operator>=(const Time &rhs) const;

    Time operator+(const Time &rhs) const;
    void operator+=(const Time& rhs);
    Time operator-(const Time& rhs) const;
    void operator-=(const Time& rhs);

    Time operator*(int i) const;

    friend std::ostream &operator<<(std::ostream &os, const Time &time);
};


#endif //UNTITLED8_TIME_H
