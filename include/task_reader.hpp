#ifndef TASKREADER_HPP
#define TASKREADER_HPP
 
#include <vector>
#include <string>
#include <fstream>

inline std::vector<std::string> readInput(std::string file_path) {
    std::ifstream file(file_path);    
    std::vector<std::string> input_vector;
    std::string row;

    while (getline(file, row)) {   
        input_vector.push_back(row);
    }
    file.close();

    return input_vector;
}

#endif // TASKREADER.hpp
