#include "game.h"
#include <iostream>
#include <thread>

Game::Game() {
    gameOver = false;
    vsCPU = true;
}


void Game::Run(Renderer &renderer, Controller &controller) {
    // Render Original Board
    renderer.Render(ultimateBoard, gameOver, ultimateBoard.winner);
    Move move;

    // Game Loop
    while(!gameOver) {
        // CPU turn path
        if (vsCPU && ultimateBoard.currentPlayer == State::Player2) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            move = bot.makeMove(ultimateBoard);
            ultimateBoard.last_CPU_move = move;
            update(ultimateBoard, move);
            renderer.Render(ultimateBoard, gameOver, ultimateBoard.winner);
        }

        // User turn path
        else {
            // Get User Input
            controller.hasMoved = false;
            move = controller.HandleInput(ultimateBoard);

            if (move.ultimate_row == -1 && move.ultimate_col == -1 && move.board_row == -1 && move.board_col == -1){
                gameOver = true;
            }
            else {
                // Update Game State
                update(ultimateBoard, move);
                // Render new board
                renderer.Render(ultimateBoard, gameOver, ultimateBoard.winner);
            }
        }
    }

    // Let the player see the end of game state (replace with Menu)
    if (move.ultimate_row != -1 && move.ultimate_col != -1 && move.board_row != -1 && move.board_col != -1) {
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }
}

void Game::update(UltimateBoard &ultimateBoard, Move &move) {
    // Make move
    ultimateBoard.boards[move.ultimate_row*3 + move.ultimate_col].tiles[(move.board_row*3 + move.board_col)].setState(ultimateBoard.currentPlayer);
    
    // check for winners and draw
    State board_winner = ultimateBoard.boards[move.ultimate_row*3 + move.ultimate_col].checkforWinner();
    if (board_winner != State::Empty) {
        ultimateBoard.boards[move.ultimate_row*3 + move.ultimate_col].winner = board_winner;
    }
    State ultimate_winner = ultimateBoard.checkforWinner();
    if (ultimate_winner != State::Empty) {
        ultimateBoard.winner = ultimate_winner;
        gameOver = true;
    }
    
    // Update active boards
    int activeBoard = move.board_row*3 + move.board_col;
    setActiveBoards(ultimateBoard,activeBoard);
    
    // Change Player
    ultimateBoard.currentPlayer = ultimateBoard.currentPlayer == State::Player1 ? State::Player2 : State::Player1;
}

void Game::setActiveBoards(UltimateBoard &ultimateBoard, int activeBoard) {
    // If board sent to is already complete set all unfinished boards to active
    if (ultimateBoard.boards[activeBoard].winner != State::Empty) {
        for (int i = 0; i < 9; i++) {
            if (ultimateBoard.boards[i].winner == State::Empty) {
                ultimateBoard.boards[i].isActive = true;
            }
            else { ultimateBoard.boards[i].isActive = false; }
        }
    }
    // If board sent to is not complete set it to active and all other inactive
    else {
        for (int i = 0; i < 9; i++) {
            ultimateBoard.boards[i].isActive = i == activeBoard ? true : false;
        }
    }
}