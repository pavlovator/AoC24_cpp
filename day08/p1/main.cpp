#include <iostream>
#include "../../include/tools.hpp"
#include <map>
#include <vector>
#include <set>

using namespace std;

struct Coords {
    int x;
    int y;
};

map<char,vector<Coords>> findAntennas(vector<string>& input) {
    map<char, vector<Coords>> antennas;
    for (int i=0; i<input.size(); i++) {
        for (int j=0; j<input.size(); j++) {
            if (input[i][j] != '.') {
                char antena = input[i][j];
                if (antennas.find(antena) == antennas.end()) {
                    antennas[antena] = vector<Coords> {{i, j}};                    
                } else {
                    antennas[antena].push_back({i, j});
                }
            }
        }
    }
    return antennas;
}

int solve(map<char,vector<Coords>>& antennas_map, vector<string>& antennas) {
    int m = antennas.size();
    int n = antennas[0].size();
    set<pair<int, int>> antinodes;
    for (const auto& p: antennas_map) {
        char a_type = p.first;
        for (int i=0; i<antennas_map[a_type].size(); i++) {
            for (int j=0; j<antennas_map[a_type].size(); j ++) {
                if (i == j) {
                    continue;
                }
                int x1 = antennas_map[a_type][i].x;
                int y1 = antennas_map[a_type][i].y;
                int x2 = antennas_map[a_type][j].x;
                int y2 = antennas_map[a_type][j].y;
                int dx = x1 - x2;
                int dy = y1 - y2;
                int anti_x = x1 + dx;
                int anti_y = y1 + dy;
                if (anti_x >= 0 && anti_x < m && anti_y >= 0 && anti_y < n) {
                    antennas[anti_x][anti_y] = '#';
                    antinodes.insert({anti_x, anti_y});
                }
            }
        }
    }
    return antinodes.size();
}

int main() {
    vector<string> antennas = readInput("../input.txt");
    map<char, vector<Coords>> antennas_map = findAntennas(antennas);  
    cout << solve(antennas_map, antennas) << endl;
}
