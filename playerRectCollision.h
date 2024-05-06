#include "C_Rect.h"
#include "Player.h"
#include "inc/SDL.h"
#include <vector>

#ifndef playerRectCollision_H
#define playerRectCollision_H

using namespace std;

bool playerRectCollision(int screenHeight, int screenWidth,
                         const vector<C_Rect> &rects, const Player &newRect) {
  for (const auto &existingRect : rects) { //rects = laser, newrect = player
    if (newRect.x + 30 <= existingRect.x + existingRect.w &&
            newRect.x + newRect.bw >= existingRect.x + 30 &&
            newRect.y + 30 <= existingRect.y + existingRect.h &&
            newRect.y + newRect.bh >= existingRect.y + 30) {
      return true; // Collision detected
    }
  }
  return false; // No collision detected
}

#endif
