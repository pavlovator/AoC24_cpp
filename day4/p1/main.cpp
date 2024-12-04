#include <iostream>
#include <string>
#include "../../include/tools.hpp"

using namespace std;

// there are eight ways to account for the XMAS string in the text matrix
//   X   S              S   X        X   S  
//    M   A            A   M         M   A        S A M X
//     A   M          M   A          A   M        X M A S
//      S   X        X   S           S   X   

int countHorizontal(vector<string>& input, int row, int col) {
    int count = 0;
    if (input[row][col] == 'X' && input[row][col+1] == 'M' &&
        input[row][col+2] == 'A' && input[row][col+3] == 'S') {
        count++;
    }
     if (input[row][col] == 'S' && input[row][col+1] == 'A' &&
        input[row][col+2] == 'M' && input[row][col+3] == 'X') {
        count++;
    }
    return count;
}

int countVertical(vector<string>& input, int row, int col) {
    int count = 0;
    if (input[row][col] == 'X' && input[row+1][col] == 'M' &&
        input[row+2][col] == 'A' && input[row+3][col] == 'S') {
        count++;
    }
     if (input[row][col] == 'S' && input[row+1][col] == 'A' &&
        input[row+2][col] == 'M' && input[row+3][col] == 'X') {
        count++;
    }
    return count;
}

// Count Diagonal from Left to Right
//   X S
//    M A
//     A M
//      S X
int countDiagonalLtoR(vector<string>& input, int row, int col) {
    int count = 0;
    if (input[row][col] == 'X' && input[row+1][col+1] == 'M' &&
        input[row+2][col+2] == 'A' && input[row+3][col+3] == 'S') {
        count++;
    }
     if (input[row][col] == 'S' && input[row+1][col+1] == 'A' &&
        input[row+2][col+2] == 'M' && input[row+3][col+3] == 'X') {
        count++;
    }
    return count;
}


// Count Diagonal from Right to Left
//       X S
//      M A
//     A M
//    S X
int countDiagonalRtoL(vector<string>& input, int row, int col) {
    int count = 0;
    if (input[row][col] == 'X' && input[row+1][col-1] == 'M' &&
        input[row+2][col-2] == 'A' && input[row+3][col-3] == 'S') {
        count++;
    }
     if (input[row][col] == 'S' && input[row+1][col-1] == 'A' &&
        input[row+2][col-2] == 'M' && input[row+3][col-3] == 'X') {
        count++;
    }
    return count;
}

int givePositionCount(vector<string>& input, int row, int col) {
    int count = 0;
    int n_rows = input.size();
    int n_cols = input[0].size();
    if (row+4 <= n_rows) {
        count += countVertical(input, row, col);
    }
    if (col+4 <= n_cols) {
        count += countHorizontal(input, row, col);  
    }
    if (row+4 <= n_rows && col+4 <= n_cols) {
        count += countDiagonalLtoR(input, row, col);
    }
    if (row+4 <= n_rows && col >= 3) {
        count += countDiagonalRtoL(input, row, col);
    }
    return count;
}


int main() {
    auto input = readInput("../input.txt");
    int count = 0;
    for (int row=0; row<input.size(); row++) {
        for (int col=0; col<input[row].size(); col++) {
            count += givePositionCount(input, row, col);
        }
    }
    cout << count << endl;
}
