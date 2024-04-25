#include "display.h"

// SDL_Surface* surface;

Display::Display(string title) {
    int w = 1024;                   // Window width
    int h = 512; 

    SDL_Window* window = NULL;

    if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        exit(1);
    }

    // window = SDL_CreateWindow(
    //         "CHIP-8 Emulator",
    //         SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    //         w, h, SDL_WINDOW_SHOWN
    // );

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);

    // cout << "created window: " << title << endl;

    // if (window == nullptr){
    //     // In the case that the window could not be made...
    //     std::cerr << "Could not create window: " << SDL_GetError( ) << std::endl;
    // } else {
    //     std::cout << "Window created." << std::endl;
    // }

    // surface = SDL_GetWindowSurface(window);
    // cout << "window surface" << endl;

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
        pixels[i] = (0x00FFFFFF * pixel) | 0xFF000000;
    }
    SDL_UpdateTexture(texture, NULL, &pixels, 64 * sizeof(Uint32));
    // Clear screen and render
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    return pixels;
}

// void set_pixel(uint16_t x, uint16_t y, uint32_t pixel) {
//     Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * 4;
//     *(Uint32 *)p = pixel;
// }



// #include <iostream>

// #include <SDL2/SDL.h>
// #include "globals.h"

// int main( int argc, char *argv[] )
// {
//     SDL_Init( SDL_INIT_VIDEO );

//     SDL_Window *window = SDL_CreateWindow( "Hello SDL World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI );
//     SDL_Renderer *renderer = nullptr;
//     SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
//     // Check that the window was successfully created
//     if ( NULL == window )
//     {
//         // In the case that the window could not be made...
//         std::cout << "Could not create window: " << SDL_GetError( ) << std::endl;
//         return 1;
//     }
    
//     SDL_Event windowEvent;
    
//     while ( true )
//     {
//         if ( SDL_PollEvent( &windowEvent ) )
//         {
//             //Probably on a loop
//             SDL_RenderDrawPoint(renderer, 400, 300); //Renders on middle of screen.
//             SDL_RenderPresent(renderer);
//             if ( SDL_QUIT == windowEvent.type )
//             {
//                 // exit(0);

//                 break;
//             }
//         }
//     }
//     SDL_DestroyWindow( window );
//     SDL_Quit( );

    
//     return EXIT_SUCCESS;
// }