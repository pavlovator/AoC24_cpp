#include "include/tools.hpp"
#include <string>
#include <iostream>


using namespace std;

int main(){
    auto split_result = split("...abec...eda...i...", "..."); // -> ["abec", "eda", "i"]
    for (auto s : split_result) {
        cout << s << " ";
    }
}
