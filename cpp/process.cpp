//
// Created by paulo on 16/08/2022.
//

#include <iostream>
#include <fstream>
#include <string>
#include "Subject.h"
#include "Timetable.h"

#define DEFAULT_FILENAME "..\\data.csv"
#define NUMBERS "0123456789"

using namespace std;

bool importContent(const string& filename, vector<Subject>& subjects){
    cout << "Opening " << filename <<  "... ";
    fstream file(filename, ios::in);
    if (file.is_open()) {
        cout << "File is open! Importing content..." << endl;
    } else {
        cout << "Couldn't open file..." << endl;
        return false;
    }

    file.ignore(512, '\n'); //ignore header
    char delim;
    while(true){
        Subject s;
        Group g;
        Lesson lesson;
        getline(file, s.abbreviation, ';');
        if(file.eof()) break;

        getline(file, g.name, ';');
        file >> lesson;

        s.type = g.name.substr(0, g.name.find_first_of(NUMBERS));

        auto sub_pos = find(subjects.begin(), subjects.end(), s);
        if(sub_pos == subjects.end()){
            g.schedule.push_back(lesson);
            s.groups.push_back(g);
            subjects.push_back(s);
        } else{
            auto group_pos = find(sub_pos->groups.begin(), sub_pos->groups.end(), g);

            if(group_pos == sub_pos->groups.end()){
                g.schedule.push_back(lesson);
                sub_pos->groups.push_back(g);
            } else {
                group_pos->schedule.push_back(lesson);
            }
        }
    }

    file.close();
    return true;
}

int menu(){
    cout << "\n=====[MENU]========================\n"
            "1 - Start Processing\n"
            "2 - Show Subjects\n"
            "3 - Toggle Subject\n"
            "4 - Filter CT modules \n"
            "5 - Glue Groups with same lessons\n"
            "0 - Exit\n"
            "=====[MENU]==========================\n";

    int option = 0;
    do {
        cout << ((option > 5 or option < 0) ? "\n invalid answer... " : "\n");
        cout << "option?";
        cin >> option;
    } while(option > 5 or option < 0);

    return option;
}

void printSubjectStatus(const vector<Subject>& subjects){
    cout << "Subjects | Type | EN? | GROUPS" << endl;
    for (const auto &s: subjects) {
        cout << left << setw(8) << s.abbreviation << " | " << setw(4) << s.type
             << " | " << ((s.enabled) ? "ON " : "OFF")  << " | " << s.groups.size() << endl;
    }
}

void toggle(bool& cond){
    if(cond){
        cond = false;
    } else {
        cond = true;
    }

}
void toggleSubject(vector<Subject>& subjects){
    printSubjectStatus(subjects);

    cout << "Subject? [(Abbreviation or #ALL) and (Type or #ALL)]";
    string abbreviation, type;
    cin >> abbreviation >> type;

    if(abbreviation == "#ALL"){
        for(auto& s : subjects){
            if(s.type == type){
                toggle(s.enabled);
            }
        }
    }else if(type == "#ALL"){
        for(auto& s : subjects){
            if(s.abbreviation == abbreviation){
                toggle(s.enabled);
            }
        }
    } else {
        Subject temp(abbreviation, type);

        auto it = find(subjects.begin(),subjects.end(),temp);
        if(it != subjects.end()){
            toggle(it->enabled);
        } else {
            cout << "can't find the subject entered..." << endl;
        }
    }


}

void removeCtModules(vector<Subject>& subjects){
    string first;
    for(const auto& s : subjects){
        if(s.abbreviation.find('(') != string::npos){
            first = s.abbreviation;
            break;
        }
    }

    for(auto s = subjects.begin(); s != subjects.end(); s++){
        if(s->abbreviation.find('(') != string::npos){
            if(first == s->abbreviation){
                s->abbreviation = "CT-I";
                for(auto &g : s->groups){
                    for(auto &l : g.schedule){
                        l.room = "-";
                    }
                }
            } else {
                subjects.erase(s);
                s -= 1;
            }
        }
    }
}

void glueDuplicatedGroups(vector<Subject>& subjects){
    for(auto& s : subjects){
        for(auto current = s.groups.begin(); current != s.groups.end(); current++){
            for(auto other = current + 1; other != s.groups.end(); other++){
                if(current->schedule == other->schedule){
                   cout << "debug: found repeated: " << s.abbreviation << ", " //debug
                        << current->name << " and " << other->name << endl;
                   current->name += (" + " + other->name);
                   for(int i = 0; i < current->schedule.size() and i < other->schedule.size(); ++i){
                       if(!(current->schedule[i].room == "-" and other->schedule[i].room == "-")){
                           current->schedule[i].room += (" + " + other->schedule[i].room);
                       }
                   }
                   s.groups.erase(other);
                   other -= 1;
                }
            }
        }
    }
}

unsigned int countPossibilities(const vector<Subject>& subjects){
    unsigned int possibilities = 1;
    for(const auto& s : subjects){
        if(s.enabled) possibilities *= s.groups.size();
    }

    return possibilities;
}

bool arrangeSubjects(const vector<Subject>& subjects,Timetable timetable,unsigned &attempt, int num = 0){
    if(num == 0){
        timetable = Timetable();
    } else if(num == subjects.size()){
        attempt++;
        timetable.exportTimetable(to_string(attempt));
        timetable.exportHtmlTimetable("..\\html\\tables\\" + to_string(attempt));
        cout << "success! " << attempt << endl;
        return true;
    } else{

    }
    Timetable backup = timetable;
    for(auto g : subjects[num].groups){
        if(timetable.addGroup(subjects[num].abbreviation, g)){
            arrangeSubjects(subjects, timetable, attempt, num + 1);
        }
        timetable = backup;
    }
    return false;
}

int main(){
    cout << "name of the file? default?";
    string filename;
    cin >> filename;
    if (filename == "default") {
        filename = DEFAULT_FILENAME;
    }

    vector<Subject> subjects;
    if(importContent(filename, subjects)){
        cout << "   -> Content Imported Successfully" << endl;
    } else {
        return 0;
    }

    while(true){
        int option = menu();
        if(option == 1) {
            break;
        } else if(option == 2) {
            printSubjectStatus(subjects);
        } else if(option == 3) {
            toggleSubject(subjects);
        } else if(option == 4) {
            removeCtModules(subjects);
        } else if(option == 5) {
            glueDuplicatedGroups(subjects);
        } else {
            cout << "bye!" << endl;
            return 0;
        }
    }



    unsigned int possibilities = countPossibilities(subjects);
    cout << "\nStarting the processing... Found " << possibilities << " possible combinations" << endl;


    for(auto it = subjects.begin(); it != subjects.end(); ++it){
        if(!it->enabled){
            subjects.erase(it);
        }
    }

    Timetable t;
    unsigned attempt = 0;
    arrangeSubjects(subjects, t, attempt);

    cout << "bye!" << endl;
    return 0;
}