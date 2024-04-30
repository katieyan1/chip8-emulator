#include "display.h"

Display::Display(string title) {
    int w = 1024; // Window width
    int h = 512; // Window height

    SDL_Window* window = NULL;

    if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        exit(1);
    }

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_RenderSetLogicalSize(renderer, w, h);

    if (renderer == nullptr) {
        std::cerr << "Couldn't initialize the renderer. Reason: " << SDL_GetError() << std::endl;
    } else {
        std::cout << "Renderer initialized." << std::endl;
    }

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

    if (texture == nullptr) {
        std::cerr << "Couldn't initialize the texture. Reason: " << SDL_GetError() << "\n";
    } else {
        std::cout << "Texture initialized." << std::endl;
    }

    SDL_DisplayMode mode;
    mode.refresh_rate = 60;
}

Display::~Display() {
    SDL_DestroyTexture(texture);
    cout << "Texture Destroyed" << endl;
    SDL_DestroyRenderer(renderer);
    cout << "Renderer Destroyed" << endl;
    SDL_DestroyWindow(window);
    cout << "Window Destroyed" << endl;
    // delete mode;
}

array<uint32_t, WIDTH * HEIGHT> Display::render(array<uint32_t, WIDTH * HEIGHT> screen) {
    array<uint32_t, WIDTH*HEIGHT> pixels;
    for (int i = 0; i < WIDTH*HEIGHT; ++i) {
        uint8_t pixel = screen[i];
        // pixels[i] = (0x00FFFFFF * pixel) | 0xFF000000;
        pixels[i] = (0x00FFFFFF * pixel) | 0x85858500;
    }
    SDL_UpdateTexture(texture, NULL, &pixels, 64 * sizeof(Uint32));
    // Clear screen and render
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    return pixels;
}