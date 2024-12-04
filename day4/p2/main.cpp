#include <iostream>
#include <string>
#include "../../include/tools.hpp"

using namespace std;

// There are 4 types of Xmas patters
//   M S     S M     M M     S S
//    A       A       A       A
//   M S     S M     S S     M M
int isXmas(vector<string>& input, int row, int col) {
    if (input[row][col] != 'A') {
        return 0;
    }
    if (input[row-1][col-1] == 'M' && input[row-1][col+1] == 'S' &&
        input[row+1][col-1] == 'M' && input[row+1][col+1] == 'S') {
        return 1;
    }
    
    if (input[row-1][col-1] == 'S' && input[row-1][col+1] == 'M' &&
        input[row+1][col-1] == 'S' && input[row+1][col+1] == 'M') {
        return 1;
    }

    if (input[row-1][col-1] == 'M' && input[row-1][col+1] == 'M' &&
        input[row+1][col-1] == 'S' && input[row+1][col+1] == 'S') {
        return 1;
    }

    if (input[row-1][col-1] == 'S' && input[row-1][col+1] == 'S' &&
        input[row+1][col-1] == 'M' && input[row+1][col+1] == 'M') {
        return 1;
    }
    return 0;
}


int main() {
    auto input = readInput("../input.txt");
    int count = 0;
    for (int row=1; row<input.size()-1; row++) {
        for (int col=1; col<input[row].size()-1; col++) {
            count += isXmas(input, row, col);
        }
    }
    cout << count << endl;
}
