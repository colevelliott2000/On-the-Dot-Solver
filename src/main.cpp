#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <tuple>

using std::vector;
// Purple, Red, Green, Yellow
vector< vector< vector<char> > > get_boards() {

    vector< vector< vector<char> > > boards;
    // Held with purple bottom left and green top right
    vector< vector<char> > board_one{
            {'N', 'N', 'N', 'N', 'N', 'N'},
            {'N', 'N', 'Y', 'N', 'N', 'N'},
            {'N', 'N', 'N', 'N', 'G', 'N'},
            {'N', 'N', 'N', 'N', 'N', 'N'},
            {'P', 'N', 'N', 'N', 'N', 'N'},
            {'N', 'N', 'N', 'N', 'R', 'N'}
            };
    // Held with red bottom left and yellow top right
    vector< vector<char> > board_two{
            {'N', 'N', 'N', 'N', 'N', 'N'},
            {'N', 'N', 'G', 'N', 'N', 'N'},
            {'N', 'N', 'N', 'N', 'Y', 'N'},
            {'N', 'N', 'N', 'N', 'N', 'N'},
            {'R', 'N', 'N', 'N', 'N', 'N'},
            {'N', 'N', 'N', 'N', 'P', 'N'}
            };
    
    // Held with green bottom left and purple top right
    vector< vector<char> > board_three{
            {'N', 'N', 'N', 'N', 'N', 'N'},
            {'N', 'N', 'R', 'N', 'N', 'N'},
            {'N', 'N', 'N', 'N', 'P', 'N'},
            {'N', 'N', 'N', 'N', 'N', 'N'},
            {'G', 'N', 'N', 'N', 'N', 'N'},
            {'N', 'N', 'N', 'N', 'Y', 'N'}
            };
    
    // Held with yellow bottom left and red top right
    vector< vector<char> > board_four{
            {'N', 'N', 'N', 'N', 'N', 'N'},
            {'N', 'N', 'P', 'N', 'N', 'N'},
            {'N', 'N', 'N', 'N', 'R', 'N'},
            {'N', 'N', 'N', 'N', 'N', 'N'},
            {'Y', 'N', 'N', 'N', 'N', 'N'},
            {'N', 'N', 'N', 'N', 'G', 'N'}
            };

    boards.push_back(board_one);
    boards.push_back(board_two);
    boards.push_back(board_three);
    boards.push_back(board_four);
    return boards;
}

vector< vector<char> > get_puzzle(std::string filename) {
    vector< vector<char> > table;
    vector<char> tmp;
    std::ifstream fin;
    char letter;
    int counter = 0;

    fin.open(filename);
    // Create 2d vector to hold the puzzle
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            fin >> letter;
            tmp.push_back(letter);
        }
        table.push_back(tmp);
        tmp.clear();
    }
    return table;
}

/* 
        Rotation
        1 = 90 deg
        2 = 180 deg
        3 = 270 deg
*/
vector< vector<char> > rotate_board(vector< vector<char> > board, int rotation) {
    vector< vector<char> > rotated_board = board;
    for (int x = 0; x < rotation; x++) {
        vector< vector<char> > tmp_final;
        for (int colNo = 0; colNo < rotated_board[0].size(); colNo++) {
            vector<char> tmp;
            for (int i = rotated_board.size() - 1; i >= 0; i--) {
                vector<char> row = rotated_board[i];
                char colVal = row.at(colNo);
                tmp.push_back(colVal);
            }
            tmp_final.push_back(tmp);
            tmp.clear();
        }
        rotated_board = tmp_final;
    }
    return rotated_board;
}

/*
        Mode
        0 = no flip
        1 = flip

*/
vector< vector<char> > flip_board(vector< vector<char> > board, int mode) {
    if (mode == 1) {
        vector< vector<char> > flipped_board{
            {board[0][5], board[0][4], board[0][3], board[0][2], board[0][1], board[0][0]},
            {board[1][5], board[1][4], board[1][3], board[1][2], board[1][1], board[1][0]},
            {board[2][5], board[2][4], board[2][3], board[2][2], board[2][1], board[2][0]},
            {board[3][5], board[3][4], board[3][3], board[3][2], board[3][1], board[3][0]},
            {board[4][5], board[4][4], board[4][3], board[4][2], board[4][1], board[4][0]},
            {board[5][5], board[5][4], board[5][3], board[5][2], board[5][1], board[5][0]},
        };
        return flipped_board;
    }
    return board;
}

vector< vector<char> > stack_boards(vector< vector<char> > board_one, vector< vector<char> > board_two, vector< vector<char> > board_three, vector< vector<char> > board_four) {
    vector< vector<char> > stacked_board = board_four;
    // Preparing my boards
    vector< vector< vector<char> > > boards;
    boards.push_back(board_three);
    boards.push_back(board_two);
    boards.push_back(board_one);

    // Iterating once per card
    for (int x = 0; x < 3; x++) {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                if (boards[x][i][j] != 'N') {
                    stacked_board[i][j] = boards[x][i][j];
                }
            }
        }
    }
    return stacked_board;
}

void print_board(vector< vector<char> > board) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

bool any_equal(int i, int j, int k, int l) {
    if (i == j || i == k || i == l || j == k || j == l || k == l) {
        return true;
    }
    return false;
}

vector<int> solve(vector< vector<char> > board) {
    vector< vector < vector<char> > > boards = get_boards();
    vector<int> return_info;
    int rot_one, rot_two, rot_three, rot_four;
    
    // Switching which card goes in the first, second, third, and fourth slot
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                for (int l = 0; l < 4; l++) {
                    // If anything any card is chosen twice, continue on the loop without checking
                    if (any_equal(i, j, k, l)) {
                       continue;
                    } 
                    // If all the cards are unique do further checking
                    else {
                        // Flip checking
                        for (int w = 0; w < 2; w++) {
                            for (int x = 0; x < 2; x++) {
                                for (int y = 0; y < 2; y++) {
                                    for (int z = 0; z < 2; z++) {
                                        // Rotation Checking
                                        for (rot_one = 0; rot_one < 4; rot_one++) {
                                            for (rot_two = 0; rot_two < 4; rot_two++) {
                                                for (rot_three = 0; rot_three < 4; rot_three++) {
                                                    for (rot_four = 0; rot_four < 4; rot_four++) {
                                                        if (stack_boards(flip_board(rotate_board(boards[i], rot_one), w), flip_board(rotate_board(boards[j], rot_two), x), flip_board(rotate_board(boards[k], rot_three), y), flip_board(rotate_board(boards[l], rot_four), z)) == board) {
                                                            return_info.push_back(i);
                                                            return_info.push_back(rot_one);
                                                            return_info.push_back(w);
                                                            return_info.push_back(j);
                                                            return_info.push_back(rot_two);
                                                            return_info.push_back(x);
                                                            return_info.push_back(k);
                                                            return_info.push_back(rot_three);
                                                            return_info.push_back(y);
                                                            return_info.push_back(l);
                                                            return_info.push_back(rot_four);
                                                            return_info.push_back(z);
                                                            return return_info;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return_info.push_back(-1);
    return return_info;
}

int main(int argc, char* argv[]) {
    // Input ./main filename
    if (argc != 2) {
        fprintf(stderr, "Usage: ./main filename.txt\n");
        exit(-1);
    }

    vector< vector<char> > table = get_puzzle(argv[1]);
    vector<int> answer = solve(table);
    if (answer[0] != -1)
        printf("Solution:\n    Rotate card #%d %d times and flip it %d times\n    Rotate card #%d %d times and flip it %d times\n    Rotate card #%d %d times and flip it %d times\n    Rotate card #%d %d times and flip it %d times\n", answer[0] + 1, answer[1], answer[2], answer[3] + 1, answer[4], answer[5], answer[6] + 1, answer[7], answer[8], answer[9] + 1, answer[10], answer[11]);
    else
        printf("Error. Could not solve.\n");
    return 0;
}