#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "globals.h"

using std::string;
using std::array;

class Display {
    public:
        SDL_Window *window{};
        SDL_Renderer *renderer{};
        SDL_Texture *texture{};
        Display(string title);
        void render(array<uint32_t, WIDTH * HEIGHT> screen);
};
