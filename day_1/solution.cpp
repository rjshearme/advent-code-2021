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

int countDepthIncreases(std::vector<int> & depths) {
    int depth_increase_count = 0;
    for (int i=1; i < depths.size(); i++) {
        if (depths[i] > depths[i-1]) {
            depth_increase_count++;
        }
    }
    return depth_increase_count;
}

void solvePart1(std::vector<std::string> & fileLines) {
    std::vector<int> depths;
    for (std::string line : fileLines) {
        depths.push_back(std::stoi(line));
    }
    int depth_increase_count = countDepthIncreases(depths);
    std::cout << "Depth increased " << depth_increase_count << " times" << std::endl;
}

void calculateDepthWindows(std::vector<int> & depthWindows, std::vector<int> & depths) {
    for (int i=2; i < depths.size(); i++) {
        int windowTotal = depths[i] + depths[i-1] + depths[i-2];
        depthWindows.push_back(depths[i] + depths[i-1] + depths[i-2]);
    }
}


void solvePart2(std::vector<std::string> & fileLines) {
    std::vector<int> depths;
    for (std::string line : fileLines) {
        depths.push_back(std::stoi(line));
    }
    std::vector<int> depthWindows;
    calculateDepthWindows(depthWindows, depths);
    int depth_increase_count = countDepthIncreases(depthWindows);
    std::cout << "Depth increased over windows " << depth_increase_count << " times" << std::endl;
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