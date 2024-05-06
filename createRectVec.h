#include "C_Rect.h"
#include "checkRectCollision.h"
#include "inc/SDL.h"
#include <random>
#include <vector>

#ifndef createRectVec_H
#define createRectVec_H

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

using namespace std;

vector<C_Rect> &createRectVec(vector<C_Rect> &rects, int numRects) {

  random_device rd;
  default_random_engine engine(rd());
  uniform_int_distribution<int> distributionX(50, SCREEN_WIDTH - 50);
  uniform_int_distribution<int> distributionY(125, SCREEN_HEIGHT - 50);

  for (auto i = 0; i < numRects; i++) {
    int randomX = distributionX(engine);
    int randomY = distributionY(engine);
    C_Rect newRect(randomX, randomY, 25, 25);

    if (!checkRectCollision(SCREEN_HEIGHT, SCREEN_WIDTH, rects, newRect)) {
      rects.push_back(newRect);
    } else {
      --i;
    }
  }
  return rects;
}

#endif
