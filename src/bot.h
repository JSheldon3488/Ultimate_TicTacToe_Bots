#ifndef BOT_H
#define BOT_H

#include <random>
#include <vector>
#include "gameObjects.h"

/* Location_Score class is used for miniMax algorithms so they can relate tile locations to a score for that location */
class Location_Score {
public:
    Location_Score() {};
    Location_Score(int score) : score(score) {};
    int row;
    int col;
    int score;
    int ultimate_row;
    int ultimate_col;
};

/* Abstract Class for all future Bots */
class Bot {
public:
    virtual Move makeMove(UltimateBoard &ultimateBoard) = 0;
    int _randomNumber(int max);
};

/* RandomBot just makes valid moves at random every time it is his turn */
class RandomBot : public Bot {
public:
    Move makeMove(UltimateBoard &ultimateBoard);
    
private:
    bool isValidMove(UltimateBoard &ultimateBoard, Move &move);
};



/* SingleBoard_miniMax bot will not look at other boards in the ultimate board. It only consideres a single
active board and solves the minimax algorithm for that board as if that was the only board it
has to worry about. If there is more then one active board it will choose a board at random and solve
the minimax algorithm for that board. If multiple moves tie for best score on a single board then it will 
choose the next move at random from the ties.*/

/* SingleBoard_miniMax Bot that will perform minimax algorithm on a single board to choose a move. */
class SingleBoard_MiniMax : public Bot {
public:
    Move makeMove(UltimateBoard &ultimateBoard);
private:
    Location_Score getBestTile(Board &board, State player, int depth);
    Location_Score randomSelectBestScore(std::vector<Location_Score> &scores, State player);
};

#endif