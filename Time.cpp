//
// Created by paulo on 14/08/2022.
//

#include "Time.h"

#include <utility>

Time::Time() {
    hours_ = 0;
    minutes_ = 0;
    seconds_ = 0;
}
Time::Time(std::string str) {
    this->setTime(std::move(str));
}
Time::Time(unsigned int hours, unsigned int minutes, unsigned int seconds) :   hours_(hours),
                                                                                minutes_(minutes),
                                                                                seconds_(seconds) {}

Time::Time(unsigned seconds){
    setTime(seconds);
}

unsigned int Time::getHours() const {
    return hours_;
}
unsigned int Time::getMinutes() const {
    return minutes_;
}
unsigned int Time::getSeconds() const {
    return seconds_;
}
std::string Time::getTime() const {
    std::string result = std::to_string(hours_) + ':' + std::to_string(minutes_) + ':' + std::to_string(seconds_);
    return result;
}

unsigned int Time::inSeconds() const{
    return 3600 * hours_ + 60 * minutes_ + seconds_;
}

unsigned int Time::inSeconds(const Time& t){
    return t.inSeconds();
}

void Time::setTime(unsigned seconds){
    hours_ = seconds / 3600;
    seconds %= 3600;
    minutes_ = seconds / 60;
    seconds %= 60;
    seconds_ = seconds;

    if(hours_ >= 24) hours_ = 0;
}
void Time::setTime(unsigned int hours, unsigned int minutes, unsigned int seconds) {
    unsigned total = 3600 * hours + 60 * minutes + seconds;
    setTime(total);
}
bool Time::setTime(std::string str) {
    if (str.find_first_not_of(TIME_STRING_CHARS) != std::string::npos){
        this->setTime("0:0:0");
        return false;
    }

    auto delimiter = std::count(str.begin(), str.end(), ':');
    unsigned pos = 0, rpos = 0, hours, minutes, seconds;

    switch(delimiter){
        case 1:
            pos = str.find(':');
            hours = stoi(str.substr(0,pos));
            minutes = stoi(str.substr(pos + 1, str.size() - pos));
            seconds = 0;
            this->setTime(hours, minutes, seconds);
            break;
        case 2:
            pos = str.find(':');
            rpos = str.rfind(':');
            hours = stoi(str.substr(0,pos));
            minutes = stoi(str.substr(pos + 1, rpos - pos));
            seconds = stoi(str.substr(rpos + 1, str.size() - rpos));
            this->setTime(hours, minutes, seconds);
            break;

        default:
            this->setTime("0:0:0");
            return false;
    }
    return true;
}

std::ostream &operator<<(std::ostream &os, const Time &time) {
    os << std::setfill('0')
       << std::setw(2) << time.hours_ << ':' << std::setw(2) << time.minutes_;

    if(time.seconds_ != 0){
        os << ':' << std::setw(2) << time.seconds_;
    }

    return os;
}

bool Time::operator==(const Time &rhs) const {
    return hours_ == rhs.hours_ &&
           minutes_ == rhs.minutes_ &&
           seconds_ == rhs.seconds_;
}
bool Time::operator!=(const Time &rhs) const {
    return !(rhs == *this);
}

bool Time::operator<(const Time &rhs) const {
    if (hours_ < rhs.hours_)
        return true;
    if (rhs.hours_ < hours_)
        return false;
    if (minutes_ < rhs.minutes_)
        return true;
    if (rhs.minutes_ < minutes_)
        return false;
    return seconds_ < rhs.seconds_;
}
bool Time::operator>(const Time &rhs) const {
    return rhs < *this;
}
bool Time::operator<=(const Time &rhs) const {
    return !(rhs < *this);
}
bool Time::operator>=(const Time &rhs) const {
    return !(*this < rhs);
}

Time Time::operator+(const Time &rhs) const {
    unsigned result_seconds = inSeconds() + rhs.inSeconds();
    return {result_seconds};
}
void Time::operator+=(const Time &rhs) {
    *this = *this + rhs;
}

Time Time::operator-(const Time &rhs) const {
    unsigned op1_seconds = inSeconds(), op2_seconds = rhs.inSeconds();
    if(op1_seconds < op2_seconds){
        op1_seconds += 24 * 3600;
    }

    return {op1_seconds - op2_seconds};
}
void Time::operator-=(const Time &rhs){
    *this = *this - rhs;
}

Time Time::operator*(int i) const {
    return {inSeconds() * i};
}