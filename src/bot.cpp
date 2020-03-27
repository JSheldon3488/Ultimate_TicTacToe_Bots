#include "bot.h"


Move RandomBot::makeMove(UltimateBoard &ultimateBoard) {
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
    Move move(board_row, board_col, row, col);
    while (!isValidMove(ultimateBoard,move)) {
        move.board_row = row_col(rng);
        move.board_col = row_col(rng);
        move.ultimate_row = row_col(rng);
        move.ultimate_col = row_col(rng);
    }
    return move;
}

bool RandomBot::isValidMove(UltimateBoard &ultimateBoard, Move &move) {
    if (ultimateBoard.boards[move.ultimate_row*3+move.ultimate_col].isActive) {
        if (!ultimateBoard.boards[move.ultimate_row*3+move.ultimate_col].tiles[(move.board_row*3+move.board_col)].isOccupied) {
            return true;
        }
    }
    return false;
}