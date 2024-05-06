#include "C_Rect.h"
#include "inc/SDL.h"
#include <vector>

#ifndef checkRectCollision_H
#define checkRectCollision_H

using namespace std;

bool checkRectCollision(int screenHeight, int screenWidth,
                        const vector<C_Rect> &rects, const C_Rect &newRect) {
  for (const auto &existingRect : rects) {
    if (newRect.x <= existingRect.x + existingRect.w &&
        newRect.x + newRect.w >= existingRect.x &&
        newRect.y <= existingRect.y + existingRect.h &&
        newRect.y + newRect.h >= existingRect.y) {
      return true; // Collision detected
    }
  }
  return false; // No collision detected
}

#endif
