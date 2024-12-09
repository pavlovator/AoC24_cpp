#include <iostream>
#include "../../include/tools.hpp"
#include <vector>
#include <map>
#include <algorithm>

using namespace std;


// returns rules in the format of key = integer and value = all the integers it should be before
map<int, vector<int>> getRules(vector<string>& input) {
    map<int, vector<int>> rules;
    for (string& row: input){
        if (row == "") {
            break;
        }
        auto split_row = split(row, '|');
        int before = stoi(split_row[0]);
        int after = stoi(split_row[1]);
        if (rules.find(before) != rules.end()) {
            rules[before].push_back(after);
        } else {
            rules[before] = {after};
        }
    }
    return rules;
}


vector<vector<int>> getSections(vector<string>& input) {
    vector<vector<int>> sections;
    bool empty = false;
    for (string& row: input) {
        if (empty){
            vector<int> int_row;
            auto split_row = split(row,',');
            for (string& s: split_row) {
                int_row.push_back(stoi(s));
            }
            sections.push_back(int_row);
        }
        if (row == "") {
            empty = true;
        }
    }
    return sections;
}

// returns 0 if it is faulty and middle value if it is correct
bool isFaulty(vector<int>& section, map<int, vector<int>>& rules) {
    for (int i=0; i<section.size(); i++) {
        for (int j=0; j<i; j++){
            if (rules.find(section[i]) == rules.end()) {
                continue;
            }
            if (find(rules[section[i]].begin(), rules[section[i]].end(), section[j]) != rules[section[i]].end()) {
                return true;
            }
        }
    }
    return false;
}

void fixSelection(vector<int>& selection, map<int, vector<int>>& rules) {
    int current = 0;
    int previous = 0;
    while (current != selection.size()) {
        previous = 0;
        while (previous != current) {
            if (find(rules[selection[current]].begin(), rules[selection[current]].end(), selection[previous]) != rules[selection[current]].end()) {
                selection.insert(selection.begin() + current + 1, selection[previous]);
                selection.erase(selection.begin() + previous);
            } else {
                previous++;
            }
        }
        current++;
    }
}

int main(){
    vector<string> input = readInput("../input.txt");
    auto sections = getSections(input);
    auto rules = getRules(input);
    int result = 0;
    for (vector<int>& section: sections) {
        if (isFaulty(section, rules)) {
            fixSelection(section, rules);
            result += section[section.size()/2];
        }
    }
    cout << "result: " << result << endl;
}
