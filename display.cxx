#include "display.h"

Display::Display(string title) {
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    if (window == nullptr){
        // In the case that the window could not be made...
        std::cerr << "Could not create window: " << SDL_GetError( ) << std::endl;
    } else {
        std::cout << "Window created." << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE);

    if (renderer == nullptr) {
        std::cerr << "Couldn't initialize the renderer. Reason: " << SDL_GetError() << std::endl;
    } else {
        std::cout << "Renderer initialized." << std::endl;
    }

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

    if (texture == nullptr) {
        std::cerr << "Couldn't initialize the texture. Reason: " << SDL_GetError() << "\n";
    } else {
        std::cout << "Texture initialized." << std::endl;
    }

    SDL_DisplayMode mode;
    mode.refresh_rate = 60;
}