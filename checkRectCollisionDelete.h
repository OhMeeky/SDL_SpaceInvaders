#include "C_Rect.h"
#include "inc/SDL.h"
#include <vector>
#include <algorithm>
#include "Player.h"

#ifndef CHECKRECTCOLLISIONDELETE_H
#define CHECKRECTCOLLISIONDELETE_H 

using namespace std; 

void checkRectCollisionDelete(int screenHeight, int screenWidth,
                         vector<C_Rect> &rects, const Player &newRect) {
    auto it = remove_if(rects.begin(), rects.end(), [&](const C_Rect &existingRect) {
        return (newRect.x <= existingRect.x + existingRect.w &&
                newRect.x + newRect.bw >= existingRect.x &&
                newRect.y <= existingRect.y + existingRect.h &&
                newRect.y + newRect.bh >= existingRect.y);
    });

    rects.erase(it, rects.end());
    
}

#endif
