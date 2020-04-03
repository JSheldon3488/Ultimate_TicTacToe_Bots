#ifndef BOT_H
#define BOT_H

#include <random>
#include "gameObjects.h"


/* Abstract Class for all future Bots */
class Bot {
public:
    virtual Move makeMove(UltimateBoard &ultimateBoard) = 0;
};

/* RandomBot just makes valid moves at random every time it is his turn */
class RandomBot : public Bot {
public:
    Move makeMove(UltimateBoard &ultimateBoard);
    
private:
    bool isValidMove(UltimateBoard &ultimateBoard, Move &move);
};

#endif