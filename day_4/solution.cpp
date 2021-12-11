#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>

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

class Tile {
    bool called;
    int value;

    public:
        Tile (int value_) {
            value = value_;
            called = false;
        }

        bool is_called() {
            return called;
        }

        void set_called() {
            called = true;
        }

        int get_value() {
            return value;
        }

};

class Board {
    std::vector<std::vector<Tile> > tiles;
    int size;

    public:
        Board (std::vector<std::vector<int> > tile_ints) {
            size = tile_ints.size();
            for (std::vector<int> tile_ints_row : tile_ints) {
                std::vector<Tile> tile_row;
                for (int tile_int : tile_ints_row) {
                    Tile tile = Tile(tile_int);
                    tile_row.push_back(tile);
                }
                tiles.push_back(tile_row);
            }
        }

        Board (std::vector<std::vector<Tile> > tiles_) {
            size = tiles_.size();
            tiles = tiles_;
        }

        Tile get_tile(int row, int col) {
            return tiles.at(row).at(col);
        }

        void call(Tile tile_called) {
            for (int row=0; row<size; row++) {
                for (int col=0; col<size; col++) {
                    Tile tile = get_tile(row, col);
                    if (tile_called.get_value() == tile.get_value()) {
                        std::cout << "Checking tile " << tile.get_value() << std::endl;
                        std::cout << "Setting tile as called - ";
                        tile.set_called();
                        std::cout << tile.is_called() << std::endl;
                    }
                }
            }
            Tile tile = get_tile(0, 0);
            Tile tile2 = tiles.at(0).at(0);
            std::cout << tile.is_called() << " " << tile2.is_called() << std::endl;
        }

        int get_unmarked_total() {
            int unmarked_total = 0;
            for (int row=0; row<size; row++) {
                for (int col=0; col<size; col++) {
                    Tile tile = get_tile(row, col);
                    if (!tile.is_called()) {
                        unmarked_total += tile.get_value();
                    };
                }
            }
            return unmarked_total;
        }

        bool is_a_bingo() {
            return is_a_vertical_bingo() or is_a_horizontal_bingo();
        }

        bool is_a_horizontal_bingo() {
            for (int row=0; row<size; row++) {
                bool horizontal_bingo = true;
                for (int col=0; col<size; col++) {
                    Tile tile = get_tile(row, col);
                    horizontal_bingo = tile.is_called() && horizontal_bingo;
                }
                if (horizontal_bingo) {
                    return horizontal_bingo;
                }
            }
            return false;
        }

        bool is_a_vertical_bingo() {
            for (int col=0; col<size; col++) {
                bool vertical_bingo = true;
                for (int row=0; row<size; row++) {
                    Tile tile = get_tile(row, col);
                    vertical_bingo = tile.is_called() && vertical_bingo;
                }
                if (vertical_bingo) {
                    return vertical_bingo;
                }
            }
            return false;
        }

        void print() {
            std::cout << "-----------------" << std::endl;
            for (int row=0; row<size; row++) {
                std::cout << "|";
                for (int col=0; col<size; col++) {
                    Tile tile = get_tile(row, col);
                    if (tile.is_called()) {
                        std::cout << " \033[1;31m" << tile.get_value() << "\033[0m ";
                    } else {
                        std::cout << " " << tile.get_value() << " ";
                    }
                }
                std::cout << "|" << std::endl;
            }
            std::cout << "-----------------" << std::endl;
        }

        void print_tiles_called() {
            std::cout << "-----------------" << std::endl;
            for (int row=0; row<size; row++) {
                std::cout << "|";
                for (int col=0; col<size; col++) {
                    Tile tile = get_tile(row, col);
                    std::cout << " " << tile.is_called() << " ";
                }
                std::cout << "|" << std::endl;
            }
            std::cout << "-----------------" << std::endl;
        }
};


std::vector<std::string> split(std::string text, char delim) {
    std::string line;
    std::vector<std::string> vec;
    std::stringstream ss(text);
    while(std::getline(ss, line, delim)) {
        if (line.length() > 0) {
            vec.push_back(line);
        }
    }
    return vec;
}

std::vector<std::vector<int> > parseTiles(std::vector<std::string> & fileLines) {
    std::vector<std::vector<int> > tiles;
    for (std::string line : fileLines) {
        std::vector<int> tileRow;
        std::vector<std::string> tileStrings = split(line, ' ');
        for (std::string tileString : tileStrings) {
            int tile = std::stoi(tileString);
            tileRow.push_back(tile);
        }
        tiles.push_back(tileRow);
    }
    return tiles;
}

std::vector<int> parseBalls(std::string line) {
    std::vector<int> bingoNumbers;
    std::vector<std::string> bingoNumbersAsString = split(line, ',');
    for (auto bingoNumberAsString : bingoNumbersAsString) {
        bingoNumbers.push_back(std::stoi(bingoNumberAsString));
    }
    return bingoNumbers;
}


class Bingo {
    std::vector<int> balls;
    std::vector<Board> boards;
    int ball_count;

    public:
        Bingo(std::vector<int> balls_, std::vector<Board> boards_) {
            balls = balls_;
            boards = boards_;
            ball_count = 0;
        }

        int play() {
            call_balls();
            Board winning_board = get_winning_board();
            int board_unmarked_total = winning_board.get_unmarked_total();
            return ball_count * board_unmarked_total;
        }

        void call_balls() {
            while (!is_winning_board() and ball_count < 11) {
                int ball = balls.at(ball_count);
                std::cout << std::endl << std::endl << "Ball played: " << ball << std::endl;
                for (Board board: boards) {
                    board.call(ball);
                    board.print();
                }
                ball_count++;
            }
        }

        Board get_winning_board() {
            for (Board board : boards) {
                if (board.is_a_bingo()) {
                    return board;
                }
            }
        }

        bool is_winning_board() {
            for (Board board : boards) {
                if (board.is_a_bingo()) {
                    return true;
                }
            }
            return false;
        }


};

std::vector<Board> parseBoards(std::vector<std::string> unparsedBoards, int board_size) {
    std::vector<Board> boards;
    int number_of_boards = unparsedBoards.size() / board_size;
    for (int board_number=0; board_number < number_of_boards; board_number++) {
        int board_offset = board_size * board_number;
        std::vector<std::string>::const_iterator firstBoardLine = unparsedBoards.begin() + board_offset;
        std::vector<std::string>::const_iterator lastBoardLine = unparsedBoards.begin() + board_size + board_offset;
        std::vector<std::string> boardLines(firstBoardLine, lastBoardLine);

        std::vector<std::vector<int>> boardTiles = parseTiles(boardLines);

        Board board = Board(boardTiles);
        boards.push_back(board);
    }
    return boards;
}

void solvePart1(std::vector<std::string> & fileLines) {
    std::string unparsedBalls = fileLines.at(0);
    std::vector<std::string> unparsedBoards (fileLines.begin()+1, fileLines.end());
    const int board_size = 5;

    std::vector<int> balls = parseBalls(unparsedBalls);
    std::vector<Board> boards = parseBoards(unparsedBoards, board_size);

    Board board = boards.at(2);
    board.print();
    board.call(14);
    board.print();

    Tile tile = board.get_tile(0, 0);
    std::cout << tile.get_value() << " " << tile.is_called() << std::endl;

    Bingo bingo = Bingo(balls, boards);
    // int winning_score = bingo.play();
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