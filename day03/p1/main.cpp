#include <iostream>
#include <string>
#include "../../include/tools.hpp"

using namespace std;
//returns 0 or result of mul operation if its in the correct format after mul(??????
int mul(string& code) {
    int result = 0;
    string num1 = "";
    string num2 = "";
    bool first_number = true;
    for (char c : code) {
        if (isdigit(c)) {
            if (first_number) {
                num1 += c;
            } else {
                num2 += c;
            }
        } else if (c == ',') {
            // if there are multiple commas
            if (!first_number) {
                return 0;
            }
            first_number = false;
        } else if (c == ')') {
            return stoi(num1) * stoi(num2);
        } else {
            return 0;
        }
    }
    return 0;
}


int main () {
    auto split_code = readInput("../input.txt"); 
    string code = "";
    for (string s : split_code) {
        code += s;
    }
    int pos = 0;
    int result = 0;
    while (true) {
        pos = code.find("mul(");
        if (pos == string::npos) {
            break;
        }
        // 4 because "mul("
        code.erase(0, pos+4);
        result += mul(code);
    }
    cout << result << endl;
}
