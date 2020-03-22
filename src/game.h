#ifndef GAME_H
#define GAME_H

#include "gameObjects.h"
#include "renderer.h"
#include "controller.h"


class Game {
public:
    Game();
    void Run(Renderer &renderer, Controller &controller);
    UltimateBoard ultimateBoard;

private:
    void update(UltimateBoard &ultimateBoard, int board, int row, int col);
    void checkforBoardWinner(Board &board);
    void checkforUltimateWinner(UltimateBoard &ultimateBoard);
    void setActiveBoards(UltimateBoard &ultimateBoard, int activeBoard);

    bool gameOver;
    bool bot;
};

#endif