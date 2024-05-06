#include "inc/SDL.h"
#include "C_Rect.h"
#include "createRectVec.h"
#include "inc/SDL_image.h"

#include <vector>
#include <iostream>


#ifndef reloadRects_H
#define reloadRects_H

using namespace std;

void reloadRects(vector<C_Rect>& rects, SDL_Renderer* renderer, int numRects, SDL_Texture* texture) {
    rects.clear();
    createRectVec(rects, numRects);

    // Clear renderer
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    if (SDL_RenderClear(renderer) != 0) {
        cerr << "SDL_RenderClear Error: " << SDL_GetError();
    }

    // Render rectangles
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    for (const auto& rect : rects) {
        rect.render(renderer, texture);
    }

    // Present the renderer
    SDL_RenderPresent(renderer);
    if (SDL_GetError() == 0) {
        std::cerr << "SDL_RenderPresent Error: " << SDL_GetError() << std::endl;
    }
}

#endif