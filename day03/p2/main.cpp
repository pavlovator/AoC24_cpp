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
    int pos_dos = -1;
    size_t pos_donts = string::npos;
    int result = 0;
    bool do_it = true;
    while (true) {
        pos_dos = code.find("do()");
        pos_donts = code.find("don't()");
        pos = code.find("mul(");
        if (pos_dos < pos && (pos < pos_donts || pos_donts == string::npos)) {
            do_it = true;
        }
        if (pos_donts < pos && pos_donts < pos_dos) {
            do_it = false;
        }

        if (pos == string::npos) {
            break;
        }
        // 4 because "mul("
        code.erase(0, pos+4);
        if (do_it) {
            result += mul(code);
        }
    }
    cout << result << endl;
}
