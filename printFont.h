#include "inc/SDL.h"
#include "C_Rect.h"
#include "createRectVec.h"
#include "inc/SDL_ttf.h"

#include <vector>
#include <iostream>


#ifndef printFont_H
#define prinfFont_H

using namespace std;




void printFont(const char* c, int x, int y, SDL_Renderer* renderer, TTF_Font* font, SDL_Color fColor) {
    // Render the text surface
    SDL_Surface* fontSurface = TTF_RenderText_Solid(font, c, fColor);
    if (fontSurface == nullptr) {
        std::cerr << "TTF_RenderText_Solid Error: " << TTF_GetError() << std::endl;
        return;
    }

    // Create texture from surface
    SDL_Texture* fontTexture = SDL_CreateTextureFromSurface(renderer, fontSurface);
    SDL_FreeSurface(fontSurface);  // Free the surface, we don't need it anymore

    if (fontTexture == nullptr) {
        std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        return;
    }

    // Query the texture for its width and height to position it correctly
    int textureWidth, textureHeight;
    SDL_QueryTexture(fontTexture, nullptr, nullptr, &textureWidth, &textureHeight);

    // Set the position of the rendered text
    SDL_Rect fontRect = {x, y, textureWidth, textureHeight};

    // Render the texture onto the renderer
    SDL_RenderCopy(renderer, fontTexture, nullptr, &fontRect);

    // Clean up the texture
    SDL_DestroyTexture(fontTexture);
}

#endif