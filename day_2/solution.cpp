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

struct Command {
    std::string direction;
    int magnitude;
};

void parseCommands(std::vector<std::string> & fileLines, std::vector<Command> & commands) {
    for (std::string line : fileLines) {
        int split_position = line.find(" ");
        std::string direction = line.substr(0, split_position);
        int magnitude = std::stoi(line.substr(split_position, std::string::npos));
        Command command;
        command.magnitude = magnitude;
        command.direction = direction;
        commands.push_back(command);
    }
}

struct Position {
    int x;
    int y;
    int aim;
};

void calculatePositionPart1(Position & position, std::vector<Command> & commands) {
    for (Command command : commands) {
        if (command.direction.compare("forward")==0) {
            position.x += command.magnitude;
        } else if (command.direction.compare("up")==0) {
            position.y -= command.magnitude;
        } else if (command.direction.compare("down")==0) {
            position.y += command.magnitude;
        } else {
            std::cerr << "Unrecognised command " << command.direction << std::endl;
            throw;
        }
    }
}

void solvePart1(std::vector<std::string> & fileLines) {
    std::vector<Command> commands;
    parseCommands(fileLines, commands);
    Position position;
    position.x = 0; position.y = 0;
    calculatePositionPart1(position, commands);
    int solution = position.x * position.y;

    std::cout << "Part 1 solution: " << solution << std::endl;
}

void calculatePositionPart2(Position & position, std::vector<Command> & commands) {
    for (Command command : commands) {
        if (command.direction.compare("forward")==0) {
            position.x += command.magnitude;
            position.y += position.aim * command.magnitude;
        } else if (command.direction.compare("up")==0) {
            position.aim -= command.magnitude;
        } else if (command.direction.compare("down")==0) {
            position.aim += command.magnitude;
        } else {
            std::cerr << "Unrecognised command " << command.direction << std::endl;
            throw;
        }
    }
}

void solvePart2(std::vector<std::string> & fileLines) {
    std::vector<Command> commands;
    parseCommands(fileLines, commands);
    Position position;
    position.x = 0; position.y = 0; position.aim = 0;
    calculatePositionPart2(position, commands);
    int solution = position.x * position.y;

    std::cout << "Part 2 solution: " << solution << std::endl;
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