#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "globals.h"

using std::string;
using std::array;

using std::cout;
using std::endl;


class Display {
    public:
        SDL_Window *window{};
        SDL_Renderer *renderer{};
        SDL_Texture *texture{};
        Display(string title);
        ~Display();
        void render(array<uint32_t, WIDTH * HEIGHT> &screen);
        
};
// void set_pixel(uint16_t x, uint16_t y, uint32_t pixel);