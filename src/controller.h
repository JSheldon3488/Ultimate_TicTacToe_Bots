#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <map>
#include <string>
#include <SDL2/SDL.h>

class Controller {
public:
    Controller(const size_t tile_width, const size_t tile_height);
    std::map<std::string, int> HandleInput();

private:
    const size_t tile_width;
    const size_t tile_height;
};

#endif