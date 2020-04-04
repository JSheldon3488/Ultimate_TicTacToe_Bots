#include "bot.h"
#include <iostream>

/***            RandomBot Implementations           ***/
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


/***            singleBoard_MiniMax Implementations           ***/
Move SingleBoard_MiniMax::makeMove(UltimateBoard &ultimateBoard) {
    //move to be returned
    Move move;

    //Get an active baord from the ultimateBoard
    Board board = getActiveBoard(ultimateBoard);
    move.ultimate_row = board.row;
    move.ultimate_col = board.col;

    //Solve miniMax algorithm to select the best tile to play on (make sure board is a copy and original not changed)
    Location_Score tile = getBestTile(board, State::Player2, 10);
    move.board_row = tile.row;
    move.board_col = tile.col;

    return move;
}

/* Returns the first active board it comes across */
Board SingleBoard_MiniMax::getActiveBoard(UltimateBoard &ultimateBoard) {
    for (Board board : ultimateBoard.boards) {
        if (board.isActive) {
            return board;
        }
    }
}

/* Recursively solves minimax for a given board to get the best move */
Location_Score SingleBoard_MiniMax::getBestTile(Board &board, State player, int depth) {
    //Base Case: Check board for winner and return proper value depending on who won
    State winner = board.checkforWinner();
    if (winner != State::Empty) {
        // AI won after last move
        if (winner == State::Player1) {
            return Location_Score(-1*depth);
        }
        // Human won last move
        else if (winner == State::Player2) {
            return Location_Score(1*depth);
        }
        // Draw make sure to set winner back to empty
        else if (winner == State::Draw) {
            return Location_Score(0);
        }
    }
    // This logic is wrong because draw will never happen!!! so idk what its doing. Its declaring draw and returning as winner!

    //Recursive Case: Solve all games down to base case and then pick best move for given player
    std::vector<Location_Score> scores;
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if ((board.tiles[row*3+col].getState() == State::Empty)) {
                Location_Score tile{0};
                tile.row = row;
                tile.col = col;
                board.tiles[row*3+col].setState(player);
                if (player == State::Player2) {
                    tile.score = getBestTile(board, State::Player1, depth-1).score;
                }
                else {
                    tile.score = getBestTile(board, State::Player2, depth-1).score;
                }
                scores.push_back(tile);
                board.tiles[row*3 + col].setState(State::Empty);
            }
        }
    }
    // For this level in the recursion pick the best move based on players perpective (min or max)
    Location_Score bestMove;
    // Bot considering best move wants the max value
    if (player == State::Player2) {
        int bestScore = -1000;
        for (auto location_score : scores) {
            if (location_score.score > bestScore) {
                bestMove = location_score;
                bestScore = location_score.score;
            }
        }
    }
    // Human picking best move wants the min value
    else {
        int bestScore = 1000;
        for (auto location_score : scores) {
            if (location_score.score < bestScore) {
                bestMove = location_score;
                bestScore = location_score.score;
            }
        }
    }
    /*
    for (auto score : scores) {
        std::cout << "(" << score.row << ", " << score.col << ", " << score.score << ")" << std::endl;
    }
    std::cout << std::endl;
    */
    return bestMove;
}