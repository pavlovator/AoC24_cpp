#ifndef TOOLS_HPP
#define TOOLS_HPP
 
#include <vector>
#include <string>
#include <fstream>
#include <string_view>


inline std::vector<std::string> readInput(std::string_view file_path) {
    std::ifstream file(file_path.data());    
    std::vector<std::string> input_vector;
    std::string row;

    while (getline(file, row)) {   
        input_vector.push_back(row);
    }
    file.close();

    return input_vector;
}

inline std::vector<std::string> split(std::string input, std::string seperator) {
    std::vector<std::string> output;
    int start = 0;
    int length = 0;
    return output;
}

#endif // TOOLS_HPP.hpp
