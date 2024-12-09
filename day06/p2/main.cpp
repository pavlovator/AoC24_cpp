#include <iostream>
#include <utility>
#include "../../include/tools.hpp"
#include <cstdlib> // For system()
#include <unistd.h>

using namespace std;

int time_s = 0;

enum class GuardState {
    Infinite,
    Out,
    InNonInfinite
};

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
    if (x >= gmap.size() || y >= gmap[0].size() || x < 0 || y < 0) {
        return true;
    }
    if (gmap[x][y] == '#') {
        return true;
    }
    return false;
}


void printGmap(vector<string>& gmap) {
    usleep(500000);
    system("clear"); // On Linux or Mac
    for (auto& row: gmap) {
        for (char c: row) {
            if (c == '>' || c == 'v' || c == '<' || c == '^') {
                cout << "\033[31m" << c << "\033[0m" << ' ';
            } else {
                cout << c << " ";
            }
        }
        cout << endl;
    }
    cout << "------------" << endl;
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
            gmap[x][y] = 'U';
            new_x = x - 1;
            new_orientation = '^';
        }
    } else if (orientation == 'v') {
        if (isObstacle(x+1, y, gmap)) {
            new_orientation = '<';
        } else {
            gmap[x][y] = 'D';
            new_x = x + 1;
            new_orientation = 'v';
        }
    } else if (orientation == '>') {
        if (isObstacle(x, y+1, gmap)) {
            new_orientation = 'v';
        } else {
            gmap[x][y] = 'R';
            new_y = y + 1;
            new_orientation = '>';
        }
    } else if (orientation == '<') {
        if (isObstacle(x, y-1, gmap)) {
            new_orientation = '^';
        } else {
            gmap[x][y] = 'L';
            new_y = y - 1;
            new_orientation = '<';
        }
    }
    guard.first = new_x;
    guard.second = new_y;
    gmap[new_x][new_y] = new_orientation;
    time_s++;
    if (time_s%6000 == 0){
        printGmap(gmap);
    }
}

GuardState guardState(vector<string>& gmap, pair<int, int>& guard) {
    int x = guard.first;
    int y = guard.second;
    if (gmap[x][y] == '>' && y == gmap[0].size()-1) {
        return GuardState::Out;
    }        
    if (gmap[x][y] == '<' && y == 0) {
        return GuardState::Out;
    }
    if (gmap[x][y] == '^' && x == 0) {
        return GuardState::Out;
    }
    if (gmap[x][y] == 'v' && x == gmap.size()-1) {
        return GuardState::Out;
    }

    if (gmap[x][y] == '>' && gmap[x][y+1] == 'R') {
        return GuardState::Infinite;
    }
    if (gmap[x][y] == '<' && gmap[x][-1] == 'L') {
        return GuardState::Infinite;
    }
    if (gmap[x][y] == '^' && gmap[x-1][y] == 'U') {
        return GuardState::Infinite;
    }
    if (gmap[x][y] == 'v' && gmap[x+1][y] == 'D') {
        return GuardState::Infinite;
    }
    return GuardState::InNonInfinite;
}


bool isInfinite(vector<string>& gmap) {
    pair<int, int> guard = findGuard(gmap);
    while (guardState(gmap, guard) != GuardState::Out) {
        if (guardState(gmap, guard) == GuardState::Infinite) {
            return true;
        }
        moveGuard(gmap, guard);
    }
    return false;
}

int main() {
    int result = 0;
    auto guard_map = readInput("../input.txt");
    for (int i=0; i<guard_map.size(); i++) {
        for (int j=0; j<guard_map[i].size(); j++) {
            cout << i << " " << j << endl;
            if (i == 17 && j == 12) {

            if (guard_map[i][j] == '.') {
                vector<string> guard_map_copy = guard_map;
                guard_map_copy[i][j] = '#';
                if (isInfinite(guard_map_copy)) {
                    result++;
                }
            }
            }
        }
    }
    cout << result << endl;
}
