#include "inc/SDL.h"
#include "inc/SDL_render.h"
#include <vector>
#include <iostream>
#include "inc/SDL_ttf.h"

#ifndef cleanUpAndQuit_H
#define cleanUpAndQuit_H

using namespace std;

void cleanupAndQuit(SDL_Window* window, SDL_Renderer* renderer) {
    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
    }
    if (window != nullptr) {
    SDL_DestroyWindow(window);
    }
    SDL_Quit();
    TTF_Quit();
    
    exit(0);
}

#endif
