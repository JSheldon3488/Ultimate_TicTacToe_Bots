#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "gameObjects.h"

int main()
{
    //Set up Necessary Variables
    const std::size_t TileWidth{120};
    const std::size_t TileHeight{120};
    const std::size_t ScreenWdith{(TileWidth*9 + 40)}; //20 for spacing between boards
    const std::size_t ScreenHeight{(TileHeight*9 + 40)};

    //Create everything needed to run the application
    //Create RenderObject
    Renderer renderer(ScreenWdith,ScreenHeight, TileWidth, TileHeight);
    //Create Test board and call Render
    UltimateBoard boards;
    boards.boards[0].grid[0].setState(State::Player1);
    boards.boards[0].grid[1].setState(State::Player2);
    boards.boards[1].grid[0].setState(State::Player1);
    boards.boards[1].grid[1].setState(State::Player2);
    boards.boards[7].grid[5].setState(State::Player1);
    boards.boards[7].grid[6].setState(State::Player2);
    boards.boards[7].isActive = false;
    renderer.Render(boards);
    //Create Controller
    //Create Game
    //Run Game
}
