#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>
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
    unordered_map<int, int> frequency_right;
    sort(right_list.begin(), right_list.end());
    int frequency = 1;
    for (int i=1; i<right_list.size(); i++) {
        if (right_list[i-1] != right_list[i]) {
            frequency_right[right_list[i-1]] = frequency;
            frequency = 1;
        } else {
            frequency++;
        }
    }
    
    // sum it all up
    int similarity_score = 0;
    for (int left : left_list) {
        similarity_score += left * frequency_right[left];
    }
    cout << "SS: " << similarity_score << endl;  
    return 0;
}
