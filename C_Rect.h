#include "inc/SDL.h"
#include "inc/SDL_image.h"

#ifndef C_RECT_H
#define C_RECT_H

class C_Rect {
public:
    int x, y, w, h;

    C_Rect(int x_pos, int y_pos, int w, int h) 
        : x(x_pos), y(y_pos), w(w), h(h) {}

    void render(SDL_Renderer *renderer, SDL_Texture* texture) const {
        SDL_Rect r = { x, y, w, h };
        // SDL_RenderDrawRect(renderer, &r);
        // SDL_RenderFillRect(renderer, &r);
        SDL_RenderCopy(renderer, texture, NULL, &r);
    }
};

#endif // C_RECT_H
