#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "../../include/tools.hpp"
using namespace std;
int main() {
    vector<int> left_list;
    vector<int> right_list;
    auto input = readInput("../input.txt");
    int left, right;
    for (string row : input) {
        stringstream ss(row);
        ss >> left >> right;
        left_list.push_back(left);
        right_list.push_back(right);
    }

        
    //make frequency table for right list 
    sort(right_list.begin(), right_list.end());
    sort(left_list.begin(), left_list.end()); 

    int result = 0;
    for (int i=0; i<right_list.size(); i++) {
        result += abs(left_list[i] - right_list[i]);
    }
    cout << result << endl; 
}
