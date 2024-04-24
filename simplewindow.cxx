#include <iostream>

#include <SDL2/SDL.h>
#include "globals.h"

int main( int argc, char *argv[] )
{
    SDL_Init( SDL_INIT_VIDEO );

    SDL_Window *window = SDL_CreateWindow( "Hello SDL World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI );
    SDL_Renderer *renderer = nullptr;
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
    // Check that the window was successfully created
    if ( NULL == window )
    {
        // In the case that the window could not be made...
        std::cout << "Could not create window: " << SDL_GetError( ) << std::endl;
        return 1;
    }
    
    SDL_Event windowEvent;
    
    while ( true )
    {
        if ( SDL_PollEvent( &windowEvent ) )
        {
            //Probably on a loop
            SDL_RenderDrawPoint(renderer, 400, 300); //Renders on middle of screen.
            SDL_RenderPresent(renderer);
            if ( SDL_QUIT == windowEvent.type )
            {
                // exit(0);

                break;
            }
        }
    }
    SDL_DestroyWindow( window );
    SDL_Quit( );

    
    return EXIT_SUCCESS;
}