#include <SDL2/SDL.h>
#include <iostream>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, char *argv[])
{
    // Variables

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    bool end = false;


    // Window

    window = SDL_CreateWindow("SDL 2.0 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if(!window)
    {
        std::cout << "SDL Error : " << SDL_GetError() << std::endl;
        return -1;
    }


    // Renderer

    renderer = SDL_CreateRenderer(window, -1, 0);

    if(!renderer)
    {
        std::cout << "SDL Error : " << SDL_GetError() << std::endl;
        return -1;
    }


    // Event loop

    while(!end)
    {
        SDL_WaitEvent(&event);

        if(event.window.event == SDL_WINDOWEVENT_CLOSE)
            end = true;


        // Drawing

        SDL_SetRenderDrawColor(renderer, 0x00, 0xAA, 0xAA, 0xFF);
        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);
    }

    return 0;
}
