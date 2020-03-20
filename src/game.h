#ifndef GAME_H
#define GAME_H

#include "gameObjects.h"
#include "renderer.h"


class Game {
public:
    Game();
    void Run(Renderer &renderer);
    UltimateBoard boards;

private:
    void update(UltimateBoard &boards, int board, int row, int col);
    bool isValidMove(UltimateBoard &boards, int board, int row, int col);
    bool checkforBoardWinner(Board &board);
    bool checkforUltimateWinner(UltimateBoard &boards);

    bool gameOver;
    State currentPlayer;
    bool bot;
};

#endif