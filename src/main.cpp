#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "board.h"

int main()
{
    //Set up Necessary Variables
    const std::size_t ScreenWdith{1100};
    const std::size_t ScreenHeight{1100};
    const std::size_t TileWdith{120};
    const std::size_t TileHeight{120};

    //Create everything needed to run the application
    //Create RenderObject
    Renderer renderer(ScreenWdith,ScreenHeight, TileWdith, TileHeight);
    //Create Test board and call Render
    while (true) {
        Board board;
        board.grid[0].setState(State::Player1);
        board.grid[1].setState(State::Player2);
        renderer.Render(board);
    }
    //Create Controller
    //Create Game
    //Run Game
}
