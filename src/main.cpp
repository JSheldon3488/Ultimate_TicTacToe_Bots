#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main()
{
    //Set up Necessary Variables
    const std::size_t ScreenWdith{720};
    const std::size_t ScreenHeight{720};
    const std::size_t TileWdith{240};
    const std::size_t TileHeight{240};

    //Create everything needed to run the application
    //Create RenderObject
    Renderer renderer(ScreenWdith,ScreenHeight, TileWdith, TileHeight);
    //Create Test board and call Render
    while (true) {
        renderer.Render(std::vector<std::string> {"x", "o", "", "", "", "", "", "", ""});
    }
    //Create Controller
    //Create Game
    //Run Game
}