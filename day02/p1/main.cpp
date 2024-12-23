#include <iostream>
#include <string>
#include "../../include/tools.hpp"

using namespace std;

vector<int> getReport(string& str_report) {
    vector<int> report;
    int beginning = 0;
    int size = 0;
    for (int i=0; i<str_report.size(); i++) {
        if (str_report[i] == ' '){
            report.push_back(stoi(str_report.substr(beginning, size)));
            beginning = i+1;
            size = 0;
        } else {
            size++;
        }
    }
    report.push_back(stoi(str_report.substr(beginning, size)));
    return report;
}

bool isCorrectAsc(vector<int>& report) {
    for (int i=1; i<report.size(); i++) {
        if (report[i-1] >= report[i] || report[i] - report[i-1] > 3) {
            return false;
        }
    }
    return true;
}

bool isCorrectDesc(vector<int>& report) {
    for (int i=1; i<report.size(); i++) {
        if (report[i-1] <= report[i] || report[i-1] - report[i] > 3) {
            return false;
        }
    }
    return true;
}

int main() {
    auto reports = readInput("../input.txt");    
    int safe_count = 0;
    for (string& str_report : reports) {
        vector<int> report = getReport(str_report);
        if (isCorrectDesc(report) || isCorrectAsc(report)) {
            safe_count++;
        }
    }
    cout << safe_count << endl;
}
