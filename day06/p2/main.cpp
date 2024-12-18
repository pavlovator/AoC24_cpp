#include <iostream>
#include <utility>
#include "../../include/tools.hpp"
#include <cstdlib> // For system()
#include <unistd.h>
#include <set>
#include <sstream>

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
    usleep(100000);
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

string visitedHash(int x, int y, char orientation) {
    ostringstream oss;
    oss << x << ' ' << y << orientation;
    return oss.str();
}

void moveGuard(vector<string>& gmap, pair<int, int>& guard, set<string>& visited) {
    char orientation = gmap[guard.first][guard.second];
    int x = guard.first;
    int y = guard.second;
    visited.insert(visitedHash(x, y, orientation));

    int new_x = x;
    int new_y = y;
    char new_orientation = '?';
    if (orientation == '^') {
        if (isObstacle(x-1, y, gmap)) {
           new_orientation = '>'; 
        } else {
            new_x = x - 1;
            new_orientation = '^';
        }
    } else if (orientation == 'v') {
        if (isObstacle(x+1, y, gmap)) {
            new_orientation = '<';
        } else {
            new_x = x + 1;
            new_orientation = 'v';
        }
    } else if (orientation == '>') {
        if (isObstacle(x, y+1, gmap)) {
            new_orientation = 'v';
        } else {
            new_y = y + 1;
            new_orientation = '>';
        }
    } else if (orientation == '<') {
        if (isObstacle(x, y-1, gmap)) {
            new_orientation = '^';
        } else {
            new_y = y - 1;
            new_orientation = '<';
        }
    }
    guard.first = new_x;
    guard.second = new_y;
    gmap[new_x][new_y] = new_orientation;
}

GuardState guardState(vector<string>& gmap, pair<int, int>& guard, set<string>& visited) {
    
    int x = guard.first;
    int y = guard.second;
    string new_hash = visitedHash(x, y, gmap[x][y]);

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
    if (visited.find(new_hash) != visited.end()) {
        return GuardState::Infinite;
    }
    return GuardState::InNonInfinite;
}


bool isInfinite(vector<string>& gmap, set<string>& visited) {
    pair<int, int> guard = findGuard(gmap);
    while (guardState(gmap, guard, visited) != GuardState::Out) {
        if (guardState(gmap, guard, visited) == GuardState::Infinite) {
            return true;
        }
        moveGuard(gmap, guard, visited);
    }
    return false;
}

int main() {
    int result = 0;
    auto guard_map = readInput("../input.txt");
    for (int i=0; i<guard_map.size(); i++) {
        for (int j=0; j<guard_map[i].size(); j++) {
            if (guard_map[i][j] == '.') {
                vector<string> guard_map_copy = guard_map;
                set<string> visited;
                guard_map_copy[i][j] = '#';
                if (isInfinite(guard_map_copy, visited)) {
                    result++;
                }
            }
        }
    }
    cout << result << endl;
}
