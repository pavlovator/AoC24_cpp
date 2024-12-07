#include <iostream>
#include <utility>
#include "../../include/tools.hpp"

using namespace std;


pair<int, int> findGuard(vector<string>& gmap) {
    for (int i=0; i<gmap.size(); i++) {
        for (int j=0; j<gmap[0].size(); j++) {
            char loc = gmap[i][j];
            if (loc == '>' || loc == '<' || loc == 'v' || loc == '^') {
                return make_pair(i, j);
            }
        }
    }
    // toto sa ani nemoze stat ak je input spravny...
    return make_pair(0, 0);
}

bool isObstacle(int x, int y, vector<string>& gmap) {
    if (x >= gmap.size() || y >= gmap[0].size() || x <= 0 || y <= 0) {
        return true;
    }
    if (gmap[x][y] == '#') {
        return true;
    }
    return false;
}

void moveGuard(vector<string>& gmap, pair<int, int>& guard) {
    char orientation = gmap[guard.first][guard.second];
    int x = guard.first;
    int y = guard.second;
    int new_x = x;
    int new_y = y;
    char new_orientation = '?';
    if (orientation == '^') {
        if (isObstacle(x-1, y, gmap)) {
           new_orientation = '>'; 
        } else {
            gmap[x][y] = 'X';
            new_x = x - 1;
            new_orientation = '^';
        }
    } else if (orientation == 'v') {
        if (isObstacle(x+1, y, gmap)) {
            new_orientation = '<';
        } else {
            gmap[x][y] = 'X';
            new_x = x + 1;
            new_orientation = 'v';
        }
    } else if (orientation == '>') {
        if (isObstacle(x, y+1, gmap)) {
            new_orientation = 'v';
        } else {
            gmap[x][y] = 'X';
            new_y = y + 1;
            new_orientation = '>';
        }
    } else if (orientation == '<') {
        if (isObstacle(x, y-1, gmap)) {
            new_orientation = '^';
        } else {
            gmap[x][y] = 'X';
            new_y = y - 1;
            new_orientation = '<';
        }
    }
    gmap[x][y] = 'X';
    guard.first = new_x;
    guard.second = new_y;
    gmap[new_x][new_y] = new_orientation;
}

void printGmap(vector<string>& gmap) {
    for (auto& row: gmap) {
        for (char c: row) {
            cout << c << " ";
        }
        cout << endl;
    }
    cout << "------------" << endl;
}

bool isOut(vector<string>& gmap, pair<int, int>& guard) {
    //printGmap(gmap);
    int x = guard.first;
    int y = guard.second;
    if (gmap[x][y] == '>' && y == gmap[0].size()-1) {
        return true;
    }        
    if (gmap[x][y] == '<' && y == 0) {
        return true;
    }
    if (gmap[x][y] == '^' && x == 0) {
        return true;
    }
    if (gmap[x][y] == 'v' && x == gmap.size()-1) {
        return true;
    }
    return false;
}


void simulate(vector<string>& gmap) {
    pair<int, int> guard = findGuard(gmap);
    while (!isOut(gmap, guard)) {
        moveGuard(gmap, guard);
    }
    gmap[guard.first][guard.second] = 'X';
}

int main() {
    int result = 0;
    auto guard_map = readInput("../input.txt");
    simulate(guard_map);
    for (auto& row: guard_map) {
        for (char c: row) {
            if (c == 'X') {
                result++;
            }
        }
    }
    cout << result << endl;
}
