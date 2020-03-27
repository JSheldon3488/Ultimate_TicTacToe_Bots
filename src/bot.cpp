#include "bot.h"


std::map<std::string,int> RandomBot::makeMove(UltimateBoard &ultimateBoard) {
    std::map<std::string, int> move;
    // Randoom Number Generator setup
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> brd(0,8);
    std::uniform_int_distribution<int> row_col(0,2);

    // Generate random numbers until its a valid move
    int row = row_col(rng);
    int col = row_col(rng);
    int board_row = row_col(rng);
    int board_col = row_col(rng);
    int board = board_row*3 + board_col;
    while (!isValidMove(ultimateBoard,board,row,col)) {
        row = row_col(rng);
        col = row_col(rng);
        board_row = row_col(rng);
        board_col = row_col(rng);
        board = board_row*3 + board_col;
    }
    
    move["board_row"] = board_row;
    move["board_col"] = board_col;
    move["board"] = board;
    move["row"] = row;
    move["col"] = col;
    return move;
}

bool RandomBot::isValidMove(UltimateBoard &ultimateBoard, const int board, const int row, const int col) {
    if (ultimateBoard.boards[board].isActive) {
        if (!ultimateBoard.boards[board].grid[(3*row + col)].isOccupied) {
            return true;
        }
    }
    return false;
}