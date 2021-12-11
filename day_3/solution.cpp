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

void solvePart1(std::vector<std::string> & fileLines) {
    int number_of_bits = fileLines.at(0).length();
    int number_of_lines = fileLines.size();
    std::string gamma_rate_string;
    std::string epsilon_rate_string;
    for (int bit_position=0; bit_position < number_of_bits; bit_position++) {
        int bit_0_count = 0;
        int bit_1_count = 0;
        for (std::string line : fileLines) {
            int line_bit = line.at(bit_position) - 48;
            if (line_bit == 0) {
                bit_0_count += 1;
            } else {
                bit_1_count += 1;
            }
        }
        if (bit_1_count > bit_0_count) {
            gamma_rate_string.append("1");
            epsilon_rate_string.append("0");
        } else {
            gamma_rate_string.append("0");
            epsilon_rate_string.append("1");
        }
    }
    int gamma_rate = std::stoi(gamma_rate_string, 0, 2);
    int epsilon_rate = std::stoi(epsilon_rate_string, 0, 2);

    std::cout << "Power consumption of the submarine is: " << gamma_rate * epsilon_rate << std::endl;
}

void solvePart2(std::vector<std::string> & fileLines) {
    int number_of_bits = fileLines.at(0).length();


}

std::string filterValues(std::vector<std::string> & values) {
    return "hello";

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