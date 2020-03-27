#ifndef GAME_H
#define GAME_H

#include "gameObjects.h"
#include "renderer.h"
#include "controller.h"
#include "bot.h"


/* Game class handles the game loop and everything else needed to run the game */
class Game {
public:
    Game();
    void Run(Renderer &renderer, Controller &controller);
    UltimateBoard ultimateBoard;

private:
    void update(UltimateBoard &ultimateBoard, Move &move);
    void checkforBoardWinner(Board &board);
    void checkforUltimateWinner(UltimateBoard &ultimateBoard);
    void setActiveBoards(UltimateBoard &ultimateBoard, int activeBoard);

    bool gameOver;
    bool vsCPU;
    RandomBot bot;
};

#endif