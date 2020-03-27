#ifndef BOT_H
#define BOT_H

#include <random>
#include "gameObjects.h"


/* RandomBot just makes valid moves at random every time it is his turn */
class RandomBot {
public:
    Move makeMove(UltimateBoard &ultimateBoard);
    
private:
    bool isValidMove(UltimateBoard &ultimateBoard, Move &move);
};

#endif