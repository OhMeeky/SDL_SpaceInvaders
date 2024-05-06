#include "inc/SDL.h"
#include "C_Rect.h"
#include <vector>
#include <iostream>


#ifndef mouseRectCollision_H
#define mouseRectCollision_H

using namespace std;

bool mouseRectCollision(int screenHeight, int screenWidth, const vector<C_Rect>& rects) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    for (const auto& existingRect : rects) {
        if (mouseX <= existingRect.x + existingRect.w &&
            mouseX >= existingRect.x &&
            mouseY <= existingRect.y + existingRect.h &&
            mouseY >= existingRect.y) {
            return true;  // Collision detected
        }
    }
    return false;  // No collision detected
}

#endif