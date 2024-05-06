#include "inc/SDL.h"
#include "C_Rect.h"
#include "checkRectCollision.h"

#include <vector>


#ifndef createInlineRect_H
#define createInlineRect_H

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

using namespace std;

vector<C_Rect>& createInlineRect(vector<C_Rect>& rectsInline, int numRects, int x, int y) {

    for(auto i = 0; i < numRects; i++) {
        C_Rect newRect(x, y, 50, 50);
        x += 160;
        if (!checkRectCollision(SCREEN_HEIGHT, SCREEN_WIDTH, rectsInline, newRect)) {
            rectsInline.push_back(newRect);
        } else {
            --i;
        }

    }
    return rectsInline;
}


#endif