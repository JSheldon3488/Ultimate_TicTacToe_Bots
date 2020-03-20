#include "game.h"
#include <iostream>
#include <thread>

Game::Game() {
    UltimateBoard boards;
    gameOver = false;
    bot = false;
}

// Add Controller once its ready
void Game::Run(Renderer &renderer, Controller &controller) {
    // Render Original Board
    renderer.Render(boards);

    // Game Loop
    while(!gameOver) {
        // Get User Input
        controller.hasMoved = false;
        controller.HandleInput(boards);

        // Update Game State

        // Render new board
        renderer.Render(boards);
    }
}

void Game::update(UltimateBoard &boards, State player, int board, int row, int col) {
    // Update boards
    // check for winners
    // update winner variables
    return;
}

bool Game::checkforBoardWinner(Board &board) {
    //Check all three rows
    //Check all three columns
    //Check two diagonals
    return true;
}

bool Game::checkforUltimateWinner(UltimateBoard &boards) {
    //Check all three rows
    //Check all three columns
    //Check two diagonals
    return true;
}