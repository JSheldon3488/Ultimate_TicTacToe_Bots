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
    // Loop until game is over
    while(!gameOver) {
        // Loop waiting for valid move
        std::cout << "Entering Handler" << std::endl;
        controller.hasMoved = false;
        controller.HandleInput(boards);
        while (!controller.hasMoved) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

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

bool Game::isValidMove(UltimateBoard &boards, int board, int row, int col) {
    // Get board from boards and check if it is Active board
    // Get Tile from given board if it was active and check if isOccupied
    // If gets threw both checks return true else return false
    return true;
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


/*
    //Test Run
    boards.boards[0].grid[0].setState(State::Player1);
    boards.boards[0].grid[1].setState(State::Player2);
    boards.boards[1].grid[0].setState(State::Player1);
    boards.boards[1].grid[1].setState(State::Player2);
    boards.boards[7].grid[5].setState(State::Player1);
    boards.boards[7].grid[6].setState(State::Player2);
    boards.boards[7].isActive = false;
    renderer.Render(boards);

    //Test Controller
    while (true) {
        std::map<std::string, int> click = controller.HandleInput();
        if (click["board"] != -2 || click["row"] != -2 || click["col"] != -2) {
            std::cout << "Board: " << click["board"] << ", Row: " << click["row"] << ", Col: " << click["col"] << std::endl;
            std::cout << "X: " << click["x"] << ", Y: " << click["y"] << std::endl;
        }
    }
*/