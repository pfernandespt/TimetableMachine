//
// Created by paulo on 18/08/2022.
//

#include "Timetable.h"

#include <utility>
#define NUMBERS "0123456789"

const std::string HTML_HEADING = "<!DOCTYPE html>\n"
                                 "<head>\n"
                                 "<link rel=\"stylesheet\" href=\"..\\style.css\">\n"
                                 "</head>\n"
                                 "<html>\n"
                                 "<body>\n"
                                 "<table>\n"
                                 "<tr>\n"
                                 "<th class=\"hour\">Horas</th>\n"
                                 "<th class=\"day\">Segunda</th>\n"
                                 "<th class=\"day\">Terça</th>\n"
                                 "<th class=\"day\">Quarta</th>\n"
                                 "<th class=\"day\">Quinta</th>\n"
                                 "<th class=\"day\">Sexta</th>\n"
                                 "<Th class=\"day\">Sábado</Th>\n"
                                 "</tr>\n";

const std::string HTML_END =  "</table>\n"
                              "</body>\n"
                              "</html>";

const Time eight_pm(20,0,0), half_hour(0,30,0);

Timetable::Timetable() {
    resetTimetable();
}

Timetable::Timetable(std::string Name) : name(std::move(Name)) {
    resetTimetable();
}

void Timetable::resetTimetable(){
    subjects.clear();

    for(auto & i : occ){
        i.clear();
    }
}

bool Timetable::isCompatible(const Lesson& l) const{
    if(occ[l.weekday].empty()){
        return true;
    }

    auto it = occ[l.weekday].begin();
    for(; it != occ[l.weekday].end();it++){
        if(it->first > l.beg){
            break;
        }
    }

    if(it == occ[l.weekday].begin()){
        if(l.end > it->first){
            return false;
        }
    }else if(it == occ[l.weekday].end()){
        if(l.beg < (--it)->second){
            return false;
        }
    }else{
        if(l.end > it->first or l.beg < (--it)->second){
            return false;
        }
    }

    return true;
}
bool Timetable::isCompatible(const Group& g) const{
    for(const auto& l : g.schedule){
        if(!isCompatible(l)){
            return false;
        }
    }
    return true;
}

bool Timetable::addGroup(const std::string &subject_abbrev, Group &group) {
    if(isCompatible(group)){
        for(const auto& l : group.schedule){
            occ[l.weekday].insert({l.beg, l.end});
        }
        subjects.insert({subject_abbrev, group});
        return true;
    }else {
        return false;
    }
}

void Timetable::exportTimetable(const std::string& filename) const {
    std::fstream file;
    file.open("..\\timetables\\" + filename + ".csv", std::ios::out);
    if(!file.is_open()){
        std::cout << "Error opening file " << name << std::endl;
    } else {
        //std::cout << "File is open" << std::endl;
    }

    file << "ABBREV;GROUP;ROOM;WEEKDAY;BEG;END#" << std::endl;

    for(auto [n, g] : subjects){
        for(const auto& l : g.schedule){
            file << n << ';' << g.name << ';' << l << std::endl;
        }
    }

    file.close();
}

void Timetable::exportHtmlTimetable(const std::string& filename) const{
    std::fstream file;
    file.open(filename + ".html", std::ios::out);
    if(!file.is_open()){
        std::cout << "Error opening file " << name << std::endl;
    } else {
        //std::cout << "File is open" << std::endl;
    }

    file << HTML_HEADING;

    bool is_filled = false;

    for(Time t(8, 0, 0); t <= eight_pm; t += half_hour){
        file << "<tr>" << std::endl; //new row
        file << "<th>" << t << "</th>" << std::endl; //time part
        for(int i = 1; i < 7; i++){
            for(const auto& [subject, group] : subjects){
                for(const auto& lesson : group.schedule){
                    if(lesson.weekday == i and lesson.beg < t and lesson.end > t){
                        is_filled = true;
                        break;
                    }
                    if(lesson.weekday == i and lesson.beg == t){
                        unsigned int rowspan = Time::inSeconds(lesson.end - lesson.beg) / (30 * 60);
                        file << "<td class=\"" << group.name.substr(0,group.name.find_first_of(NUMBERS)) << "\" rowspan=\"" << rowspan << "\">"
                             << "<span class=\"subject\">" << subject
                             << "</span><span class=\"info\">" << group.name
                             << "</span>" << std::endl;
                        is_filled = true;
                        break;
                    }
                }

            }
            if(!is_filled){
                file << "<td class=\"filling\"></td>" << std::endl;
            }
            is_filled = false;
        }
        file << "</tr>" << std::endl;
    }

    file << HTML_END;
    file.close();

}









