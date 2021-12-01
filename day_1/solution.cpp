#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

bool readFileContent(std::string fileName, std::vector<std::string> & fileLines) {
    std::ifstream in(fileName.c_str());
    if(!in) {
        std::cerr << "Cannot open the file: " << fileName << std::endl;
        return false;
    }

    std::string str;
    while (std::getline(in, str)) {
        if(str.size() > 0) {
            fileLines.push_back(str);
        }
    }
    in.close();
    return true;
}

int countDepthIncreases(std::vector<std::string> & depths) {
    int depth_increase_count;
    for (int i=1; i < depths.size(); i++) {
        if (depths[i] > depths[i-1]) {
            depth_increase_count++;
        }
    }

    return depth_increase_count;
}

void solvePart1(std::vector<std::string> & fileLines) {
    int depth_increase_count = countDepthIncreases(fileLines);
    std::cout << "Depth increased " << depth_increase_count << " times" << std::endl;
}


void solvePart2(std::vector<std::string> & fileLines) {
    std::cout << "Part 2 solved" << std::endl;
}

int readPartNumber(char* argv[]) {
    return atoi(argv[1]);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: <part_number> <input_file>" << std::endl;
        return 1;
    }

    int partNumber = readPartNumber(argv);


    char* fileName = argv[2];
    std::vector<std::string> fileLines;
    bool result = readFileContent(fileName, fileLines);
    if(!result)  {
        return 1;
    }

    if (partNumber == 1) {
        solvePart1(fileLines);
    } else if (partNumber == 2) {
        solvePart2(fileLines);
    }

    return 0;
}