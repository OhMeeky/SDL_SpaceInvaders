#include "inc/SDL.h"
#include "inc/SDL_render.h"
#include <vector>
#include <iostream>
#include "cleanUpAndQuit.h"
#include "C_Rect.h"
#include "reloadRects.h"
#include "mouseRectCollision.h"
#include "deleteRect.h"
#include "Player.h"
#include "inc/SDL_image.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#ifndef pollEvent_H
#define pollEvent_H

using namespace std;

void pollEvent(SDL_Window* window, SDL_Renderer* renderer, SDL_Event event, \
        int numRects, vector<C_Rect>& rects, Player player, int xvel, int yvel, int vel, SDL_Texture* texture) {

        while(SDL_PollEvent(&event)){
            int is_pressed = event.key.state == SDL_PRESSED;
            SDL_Keycode key = event.key.keysym.sym;
            switch (event.type){
                case (SDL_KEYDOWN):
                switch (event.key.keysym.sym){
                
                case SDLK_ESCAPE: 
                    cleanupAndQuit(window, renderer);
                    break;

                case SDLK_r:
                    reloadRects(rects, renderer, numRects, texture);
                    break;

                case SDLK_UP:          
                    rects.push_back(createRectVec(rects, 0)[0]);
                    numRects++;
                    cout << "numRects: " << numRects << " rects size: " << rects.size() << endl;
                    reloadRects(rects, renderer, numRects, texture);
                    break;
                
                case SDLK_DOWN:
                    rects.pop_back();
                    numRects--;
                    cout << "numRects: " << numRects << " rects size: " << rects.size() << endl;
                    reloadRects(rects, renderer, numRects, texture);
                    break;
                
                
                case SDLK_w: 
                    yvel = -vel;
                    cout << "wwwwwww down player\n";
                    //y += yvel;
                    break;
            
                case SDLK_s:
                    yvel = vel;
                    cout << "ssssss down player\n";
                    //y += yvel;
                    break;    
                
                case SDLK_a:
                    xvel = -vel;
                    cout << "aaaaaaaa down player\n";
                    //x += xvel;
                    break;
                
                case SDLK_d:
                    xvel = vel; 
                    cout << "dddddd down player\n";
                   // x += xvel;
                    break;
             
            
            break;
            case SDL_KEYUP:
                switch( event.key.keysym.sym ){
                    case SDLK_w:
                        cout << "key up!\n";
                        if(yvel < 0){
                            yvel = 0;
                        }
                        //y += yvel;
                        break;
                    case SDLK_s:
                        if(xvel > 0){
                            yvel = 0;
                        }
                        //y += yvel;
                        break;
                    case SDLK_a:
                        if(xvel < 0){
                            xvel = 0;
                        }
                       // x += xvel;
                        break;
                    case SDLK_d:
                        if(xvel > 0){
                            xvel = 0;
                        }
                        //x += xvel;
                        break;

                }
            }
                    
            }         
            if(event.type == SDL_MOUSEBUTTONDOWN){
                    if(event.button.button == SDL_BUTTON_LEFT &&
                        mouseRectCollision(SCREEN_HEIGHT, SCREEN_WIDTH, rects)) {
                        deleteRect(SCREEN_HEIGHT, SCREEN_WIDTH, rects);
                        cout << "Mouse Rect Collision Detected" << endl;
                    }
                }
            } 
    cout << "xvel: " << xvel << "yvel: " << yvel << '\n';  
    player.x += 10;
    player.y += yvel;
}        

#endif
