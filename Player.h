#include "inc/SDL.h"
#include "inc/SDL_image.h"

#ifndef  Player_H
#define  Player_H

#include <iostream>
using namespace std;

class Player {
public:
    int x, y, bw, bh;

    Player(int base_x_pos, int base_y_pos, int base_w, int base_h) 
        : x(base_x_pos), y(base_y_pos), bw(base_w), bh(base_h) {}

    // SDL_Surface* surface = IMG_Load("image.png");
    // SDL_Texture* texture = SDL_CreateTextureFromSurface(SDL_Renderer *renderer, surface);

    void render(SDL_Renderer *renderer, SDL_Texture* texture) const {
        SDL_Rect bottomRect = { x, y, bw, bh };
        // SDL_Rect topRect = { x+tw, y-th, tw, th };

        SDL_RenderCopy(renderer, texture, NULL, &bottomRect);



        // SDL_RenderDrawRect(renderer, &bottomRect);
        // SDL_RenderFillRect(renderer, &bottomRect);



        
        // SDL_RenderDrawRect(renderer, &topRect);
        // SDL_RenderFillRect(renderer, &topRect);

    }

    void moveUp() {
       
    }
    void moveDown() {
      
    }
    void moveLeft() {
       
    }
    void moveRight() {
      
    }


};

#endif 
