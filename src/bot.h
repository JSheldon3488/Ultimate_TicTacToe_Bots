#ifndef BOT_H
#define BOT_H

#include <random>
#include <map>
#include <string>
#include "gameObjects.h"


class RandomBot {
public:
    std::map<std::string, int> makeMove(UltimateBoard &ultimateBoard);
    
private:
    bool isValidMove(UltimateBoard &ultimateBoard, const int board, const int row, const int col);
};

#endif