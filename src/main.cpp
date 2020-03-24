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
    Renderer renderer(ScreenWdith,ScreenHeight, TileWidth, TileHeight);
    Controller controller(TileWidth, TileHeight);
    Game game;
    //Run Game
    game.Run(renderer, controller);
}
