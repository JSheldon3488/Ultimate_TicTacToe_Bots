#include "bot.h"
#include <iostream>
#include <thread>

/***            Utility stuff for all bots to use           ***/
int Bot::_randomNumber(int max) {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uniform_dist(0,max);
    return uniform_dist(rng);
}

/***            RandomBot Implementations           ***/
Move RandomBot::makeMove(UltimateBoard &ultimateBoard) {
    // Generate random numbers until its a valid move
    int row = _randomNumber(2);
    int col = _randomNumber(2);
    int board_row = _randomNumber(2);
    int board_col = _randomNumber(2);
    Move move(board_row, board_col, row, col);
    while (!isValidMove(ultimateBoard,move)) {
        move.board_row = _randomNumber(2);
        move.board_col = _randomNumber(2);
        move.ultimate_row = _randomNumber(2);
        move.ultimate_col = _randomNumber(2);
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

    // Find index of all possible active boards (more efficient to push in index then a board)
    std::vector<int> active;
    for (Board board : ultimateBoard.boards) {
        if (board.isActive) {
            active.push_back(board.row*3+board.col);
        }
    }

    // If more then one active board run the getBestTile on all boards and pick the best move (break ties randomly)
    if (active.size() > 1) {
        std::vector<Location_Score> location_scores;
        //Find the max score
        int maxScore = -10000;
        for (int i : active) {
            Location_Score location_score = getBestTile(ultimateBoard.boards[i], Player2, 10);
            location_score.ultimate_row = ultimateBoard.boards[i].row;
            location_score.ultimate_col = ultimateBoard.boards[i].col;
            location_scores.push_back(location_score);
            if (location_score.score > maxScore) {
                maxScore = location_score.score;
            }
        }

        //Get all boards with the maxScore and select one by breaking ties randomly
        std::vector<Location_Score> temp;
        for (auto l_score : location_scores) {
            if (l_score.score == maxScore) {
                temp.push_back(l_score);
            }
        }

        // Check that he is selecting random
        for (auto t : temp) {
            std::cout << "Board: " << t.ultimate_row << "," << t.ultimate_col << " Score: " << t.score << std::endl;
        }
        std::cout << std::endl;

        Location_Score randomBestMove = temp[_randomNumber(temp.size()-1)];
        move.ultimate_row = randomBestMove.ultimate_row;
        move.ultimate_col = randomBestMove.ultimate_col;
        move.board_row = randomBestMove.row;
        move.board_col = randomBestMove.col;
        return move;
    }

    // Else solve miniMax algorithm on the only active board
    Location_Score tile = getBestTile(ultimateBoard.boards[active[0]], State::Player2, 10);
    move.ultimate_row = ultimateBoard.boards[active[0]].row;
    move.ultimate_col = ultimateBoard.boards[active[0]].col;
    move.board_row = tile.row;
    move.board_col = tile.col;
    return move;
}

/* Recursively solves minimax for a given board to get the best move */
Location_Score SingleBoard_MiniMax::getBestTile(Board &board, State player, int depth) {
    //If the board is empty dont waste the time on miniMax because all scores will be 0
    bool isEmpty = true;
    for (Tile tile : board.tiles) {
        if (tile.isOccupied) {
            isEmpty = false;
            break;
        }
    }
    if (isEmpty) {
        Location_Score tile{0};
        tile.row = _randomNumber(2);
        tile.col = _randomNumber(2);
        return tile;
    }

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
    return randomSelectBestScore(scores, player);
}

Location_Score SingleBoard_MiniMax::randomSelectBestScore(std::vector<Location_Score> &scores, State player) {
    // Find the best scores
    int bestScore;
    // Bot picking the best move wnats the max value
    if (player == State::Player2) {
        bestScore = -1000;
        for (auto location_score : scores) {
            if (location_score.score > bestScore) {
                bestScore = location_score.score;
            }
        }
    }
    // Human picking best move wants the min value
    else {
        bestScore = 1000;
        for (auto location_score : scores) {
            if (location_score.score < bestScore) {
                bestScore = location_score.score;
            }
        }
    }

    // Put all the scores that match the best score into a vector and then select one at random
    std::vector<Location_Score> temp;
    for (auto score : scores) {
        if (score.score == bestScore) {
            temp.push_back(score);
        }
    }
    int rand = _randomNumber(temp.size()-1);
    return temp[rand];
}
