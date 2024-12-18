#include "../../include/tools.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<long> giveExpression(string &digits) {
    vector<long> res;
    auto tmp = split(digits, ' ');
    for (string &s : tmp) {
      if (!s.empty()) {
        res.push_back(stol(s));
      }
    }
    return res;
}

void generateCombinations(string current, vector<string> &combinations,
                          const vector<char> &symbols, int size) {
    if (current.size() == size) {
      combinations.push_back(current);
      return;
    }
    for (char c : symbols) {
      generateCombinations(current + c, combinations, symbols, size);
    }
}

long solve(vector<long> &exp, long solution) {
    vector<string> combinations;
    vector<char> symbols = {'*', '+'};
    generateCombinations("", combinations, symbols, exp.size() - 1);
    
    for (string &combination : combinations) {
      long res_comb = 0;
      for (int i = 0; i < combination.size(); i++) {
        char op = combination[i];
        if (op == '+') {
          if (i == 0) {
            res_comb = exp[0] + exp[1];
          } else {
            res_comb += exp[i + 1];
          }
        } else if (op == '*') {
          if (i == 0) {
            res_comb = exp[0] * exp[1];
          } else {
            res_comb *= exp[i + 1];
          }
        }
      }
      if (res_comb == solution) {
        return solution;
      }
    }
    return 0;
}

int main() {
    auto input = readInput("../input.txt");
    long res = 0;
    for (auto &eq : input) {
      auto tmp = split(eq, ':');
      long solution = stol(tmp[0]);
      vector<long> expression = giveExpression(tmp[1]);
      long a = solve(expression, solution);
      res += a;
    }
    cout << res << endl;
}
