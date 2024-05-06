#include "inc/SDL.h"
#include "C_Rect.h"
#include <vector>


#ifndef deleteRect_H
#define deleteRect_H


#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

using namespace std;

void deleteRect(int screenHeight, int screenWidth, std::vector<C_Rect>& rects) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    // Use an iterator to traverse the vector
    for (auto i = rects.begin(); i != rects.end(); ++i) {
        const C_Rect& existingRect = *i;

        if (mouseX >= existingRect.x && mouseX <= existingRect.x + existingRect.w &&
            mouseY >= existingRect.y && mouseY <= existingRect.y + existingRect.h) {
            // Remove the rectangle from the vector
            i = rects.erase(i);
            // Adjust iterator to stay at the correct position after erasing
            --i;
        }
    }
}

#endif