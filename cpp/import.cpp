#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "RawData.h"

#define DEFAULT_FILENAME "..\\horarios.html" //used when default keyword is inputted
#define OPTION_SELECTED "<option selected"
#define CONTENT_TABLE "id=\"gvHorario\""
#define NAMES_TABLE "id=\"gvLegenda\""
#define TABLE_END "</table>"
#define END_OF_FILE "</html>"


using namespace std;

int main() {
    cout << "name of the file? default?";
    string filename;
    cin >> filename;
    if (filename == "default") {
        filename = DEFAULT_FILENAME;
    }

    cout << "Opening " << filename <<  "... ";
    fstream file(filename, ios::in);
    if (file.is_open()) {
        cout << "File is open!" << endl;
    } else {
        cout << "Couldn't open file..." << endl;
        return 0;
    }

    vector<RawData> content_table;
    map<string, string> names_table;
    string line, content;
    unsigned int line_number = 0; //debug

    cout << "\nDocument options chose by the user: " << endl;
    while (file.is_open()) {
        getline(file, line);
        line_number++; //debug
        if (line.find(OPTION_SELECTED) != string::npos) {
            unsigned int beg_pos, end_pos;
            beg_pos = line.find_first_of('>') + 1;
            end_pos = line.find_last_of('<');
            content = line.substr(beg_pos, end_pos - beg_pos);
            cout << "   -> " << content << endl;
        } else if (line.find(CONTENT_TABLE) != string::npos) {
            cout << "\nImporting content table... ";
            unsigned long long start, end;

            while (file.is_open()) {
                getline(file, line);
                line_number++;

                if (line.find(TABLE_END) != string::npos) {
                    break;
                }

                while (true) {
                    if (line.find("<td") == string::npos or line.find("</td>") == string::npos) break;

                    start = line.find("<td");
                    end = line.find("</td>");
                    content = line.substr(start + 4, end - start - 3);

                    if (content.find("event") != string::npos) {
                        //cout << content << "\n\n"; //debug
                        content_table.emplace_back(content);
                    }

                    line.replace(start, 1, "*");
                    line.replace(end, 1, "*");
                }
            }
        } else if (line.find(NAMES_TABLE) != string::npos) {
            unsigned long long beg_pos, end_pos;
            string abbreviation, name;

            while (file.is_open()) {
                getline(file, line);
                line_number++;

                if (line.find(TABLE_END) != string::npos) {
                    break;
                } else if (line.find("<td") != string::npos) {
                    //cout << "debug: " << line << "\n\n"; //debug

                    beg_pos = line.find("\">") + 2;
                    end_pos = line.find('<', beg_pos);
                    abbreviation = line.substr(beg_pos, end_pos - beg_pos);

                    beg_pos = line.rfind("\">") + 2;
                    end_pos = line.find('<', beg_pos);
                    name = line.substr(beg_pos, end_pos - beg_pos);

                    names_table.insert({abbreviation, name});
                }
            }

        } else if (line.find(END_OF_FILE) != string::npos) break;
    }
    file.close();
    cout << "Done, saving data... " << endl;

    //exporting content to file /////////////////////////////////////////////////////////////////////////////////////

    sort(content_table.begin(), content_table.end());

    file.open("data.csv", ios::out);
    if (!file.is_open()) {
        cout << "  -> Can't create content file..." << endl;
    } else {
        file << "SUBJECT;GROUP;ROOM;DAY;BEG;END#" << endl;
        for (const auto &o: content_table) {
            file << o << endl;
        }

        cout << "   -> Content saved successfully!" << endl;
    }

    file.close();

    // exporting names to file /////////////////////////////////////////////////////////////////////////////////////

    file.open("names.csv", ios::out);
    if(!file.is_open()){
        cout << "   -> Can't create names file..." << endl;
        return 0;
    } else {
        file << "ABBREV;NAME#" << endl;
        for (auto [a, n] : names_table){
            file << a << ';' << n << endl;
        }

        cout << "   -> Names saved successfully!" << endl;

    }

    file.close();

    cout << "\n Bye!" << endl;
    return 0;
}
