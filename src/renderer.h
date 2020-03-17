#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "game.h"


class Renderer {
public:
    Renderer(const std::size_t screen_width, const std::size_t screen_height, const std::size_t tile_width, const std::size_t tile_height);
    ~Renderer();
    void Render(std::vector<std::string> board);
    void UpdateWindowTitle();

private:
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    const std::size_t screen_width;
    const std::size_t screen_height;
    const std::size_t tile_width;
    const std::size_t tile_height;
};

#endif