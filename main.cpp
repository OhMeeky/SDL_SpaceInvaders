// ######################
// #                    #
// #   @OhMeeky 99.99%  #
// #   @Frost3z 0.01%   #
// #                    #
// ######################



#include "inc/SDL.h"
#include "inc/SDL_events.h"
#include "inc/SDL_render.h"
#include "inc/SDL_stdinc.h"
#include "inc/SDL_timer.h"
#include "inc/SDL_ttf.h"
#include "inc/SDL_image.h"

#include "C_Rect.h"
#include "checkRectCollisionDelete.h"
#include "checkRectCollision.h"
#include "createInlineRect.h"
#include "createRectVec.h"
#include "mouseRectCollision.h"
#include "pollEvent.h"
#include "printFont.h"
#include "reloadRects.h"
// #include "deleteRect.h"
#include "Player.h"
#include "playerRectCollision.h"
#include "Timer.h"

#include <cstdint>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <stdlib.h>


using namespace std;

#undef main

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

SDL_Surface* backgroundImageSurface = IMG_Load("images/bckgrnd.png");
SDL_Surface* surface = IMG_Load("images/player.png");
SDL_Surface* coinSurface = IMG_Load("images/coin.png");
SDL_Surface* laserSurface = IMG_Load("images/laser.png");
SDL_Surface* laserVSurface = IMG_Load("images/laserVertical.png");
SDL_Surface* heartSurface = IMG_Load("images/heart.png");



SDL_Surface *fontSurface;
SDL_Color fColor;
TTF_Font *font;
SDL_Rect fontRect;

random_device rd;
default_random_engine engine(rd());
uniform_int_distribution<int> distributionX(0, SCREEN_WIDTH);
uniform_int_distribution<int> distributionY(0, SCREEN_HEIGHT);


bool checkWindowCollision(int screenHeight, int screenWidth,
                          vector<C_Rect> &rect) {
  for (int i = 0; i < rect.size(); ++i) {

    if (rect[i].x < 0 || rect[i].x + rect[i].w > screenWidth || rect[i].y < 0 ||
        rect[i].y + rect[i].h > screenHeight) {
      return true;
    }
  }
  return false;
}

void moveRectRight(C_Rect *rect, bool (*checkCollision)(int, int, vector<C_Rect> &),
              vector<C_Rect> movingRects) {
  int randomY = distributionY(engine);
  int movementDirection =
      1;   int MOVEMENT_SPEED = 10;

  (*rect).x += movementDirection * MOVEMENT_SPEED;
  vector<C_Rect> tempVector{*rect};

  if (checkCollision(SCREEN_HEIGHT, SCREEN_WIDTH, tempVector)) {
    int addToNotCollide = 22; 
    (*rect).x = 0;
    for (int i = 0; i < tempVector.size(); i++) {
      if (!checkRectCollision(SCREEN_HEIGHT, SCREEN_WIDTH, tempVector, (*rect))){
      rect->y = randomY;
      cout << "checkRectCollision: " << rect->y << '\n';
      addToNotCollide += 220;
    }
    } 
  }
}
void moveRectLeft(C_Rect *rect, bool (*checkCollision)(int, int, vector<C_Rect> &),
              vector<C_Rect> movingRects) {
  int randomY = distributionY(engine);
  int movementDirection =
      -1;   int MOVEMENT_SPEED = 10;
  
  (*rect).x += movementDirection * MOVEMENT_SPEED;
  vector<C_Rect> tempVector{*rect};

  if (checkCollision(SCREEN_HEIGHT, SCREEN_WIDTH, tempVector)) {
    (*rect).x = 1220;
    for (int i = 0; i < tempVector.size(); i++) {
      if (!checkRectCollision(SCREEN_HEIGHT, SCREEN_WIDTH, tempVector, (*rect))){
      rect->y = randomY;
      cout << "checkRectCollision: " << rect->y << '\n';
    }
    } 
  }
}
void moveRectHigh(C_Rect *rect, bool (*checkCollision)(int, int, vector<C_Rect> &),
              vector<C_Rect> rectsInline) {
  int randomY = distributionY(engine);
  int movementDirection =
      1;   int MOVEMENT_SPEED = 5;
  
  (*rect).y += movementDirection * MOVEMENT_SPEED;
  vector<C_Rect> tempVector{*rect};

  if (checkCollision(SCREEN_HEIGHT, SCREEN_WIDTH, tempVector)) {
    (*rect).y = 0;
    for (int i = 0; i < tempVector.size(); i++) {
    } 
  }
}
int main(int argc, char **argv) {

  int velX = 0;
  int velY = 0;

    // Timing constants
  const int UPDATE_FREQUENCY{ 144 };
  const float CYCLE_TIME{ 1.0f / UPDATE_FREQUENCY };
    // System timing
  static Timer system_timer;
  float accumulated_seconds{ 0.0f };



  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Error: SDL failed to initialize\nSDL Error: '%s'\n",
           SDL_GetError());
    return 1;
  }

  SDL_Window *window =
      SDL_CreateWindow("SDL Example", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  if (window == nullptr) {
    std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
    SDL_Quit();
    return 1;
  }



  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_Texture* backgroundImage = SDL_CreateTextureFromSurface(renderer, backgroundImageSurface);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_Texture* coinTexture = SDL_CreateTextureFromSurface(renderer, coinSurface);
  SDL_Texture* laserTexture = SDL_CreateTextureFromSurface(renderer, laserSurface);
  SDL_Texture* laserVTexture = SDL_CreateTextureFromSurface(renderer, laserVSurface);
  SDL_Texture* heartTexture = SDL_CreateTextureFromSurface(renderer, heartSurface);
  


  SDL_FreeSurface(backgroundImageSurface); // Free the surface, as it's no longer needed
  SDL_FreeSurface(surface);
  SDL_FreeSurface(coinSurface);
  SDL_FreeSurface(laserSurface);
  SDL_FreeSurface(laserVSurface);
  SDL_FreeSurface(heartSurface);


  if (renderer == nullptr) {
    std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(backgroundImage);
    SDL_Quit();
    return 1;
  }
  if (TTF_Init() == -1) {
    std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
    // Handle initialization error...
  }

  // Load font
  font = TTF_OpenFont("./Arial.ttf", 24);
  fColor = {255, 255, 255};
  if (font == nullptr) {
    std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
    // Handle font loading error...
  }

  random_device rd;
  default_random_engine engine(rd());
  uniform_int_distribution<int> distributionX(10, SCREEN_WIDTH);
  uniform_int_distribution<int> distributionY(50, SCREEN_HEIGHT);

  bool collisionStarted1 = false;
  bool collisionStarted2 = false;
  bool collisionStarted3 = false;
  bool collisionPlayerLives = false;
  bool collisionPoint = false;
  bool canSpawnLives = true;

  int lives = 3;
  int points = 0;

  vector<C_Rect> rects;
  vector<C_Rect> pointsV;
  vector<C_Rect> rectsInline;
  
  int rectsInlineSpeed = 0;
  int numRects = 4;

  // createInlineRect(rectsInline, 22, -10, 100);
  createInlineRect(rectsInline, 4, 380, 0);

  vector<C_Rect> movingRectsRight = {};  
  vector<C_Rect> movingRectsLeft = {};  
  for (int i = 0; i < 2; i++) {
    int randomY = distributionY(engine);
    int randomX = distributionX(engine);
    C_Rect movingRect = {randomX, randomY, 50, 50};
    if (!checkRectCollision(SCREEN_HEIGHT, SCREEN_WIDTH, movingRectsRight,
                            movingRect)) {
      movingRectsRight.push_back(movingRect);
    } else {
      i--;
    }
  }

  for (int i = 0; i < 2; i++) {
    int randomY = distributionY(engine);
    int randomX = distributionX(engine);
    C_Rect movingRect = {randomX, randomY, 50, 50};
    if (!checkRectCollision(SCREEN_HEIGHT, SCREEN_WIDTH, movingRectsLeft,
                            movingRect)) {
      movingRectsLeft.push_back(movingRect);
    } else {
      i--;
    }
  }

  // x_pos - y_pos - w - h
  Player player = {1000, 600, 60, 60};

  bool pressW, pressS, pressA, pressD;

  createRectVec(pointsV, 5);

  Uint32 startTime = SDL_GetTicks();
  
  bool running = true;
  while (running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {

      SDL_Keycode key = event.key.keysym.sym;
      switch (event.type) {
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {

        case SDLK_ESCAPE:
          cleanupAndQuit(window, renderer);
          break;

        case SDLK_w:
          pressW = true;
          break;

        case SDLK_s:
          pressS = true;
          break;

        case SDLK_a:
          pressA = true;
          break;

        case SDLK_d:
          pressD = true;
          break;
        }
        break;
          
      case SDL_KEYUP:
        switch (event.key.keysym.sym){
        case SDLK_w:
          pressW = false;
          break;

        case SDLK_s:
          pressS = false;
          break;

        case SDLK_a:
          pressA = false;
          break;

        case SDLK_d:
          pressD = false;
          break;
        }
        break;
      
      
      }
      if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT &&
            mouseRectCollision(SCREEN_HEIGHT, SCREEN_WIDTH, rects)) {
          deleteRect(SCREEN_HEIGHT, SCREEN_WIDTH, rects);
        }
      }
    }
    int randomY = distributionY(engine);
    int randomX = distributionX(engine);
    C_Rect movingRect = {randomX, randomY, 50, 20};



    if(points >= 15) {
    for (auto &rect : rectsInline) {
      moveRectHigh(&rect, checkWindowCollision, rectsInline);
      }
      if(movingRectsLeft.size() <=3) {
        movingRectsLeft.push_back(movingRect);
      }
      if(movingRectsRight.size() <=3) {
        movingRectsRight.push_back(movingRect);
      }
    } else if(points >= 30) {
      if(movingRectsLeft.size() <=4) {
        movingRectsLeft.push_back(movingRect);
      }
      if(movingRectsRight.size() <=4) {
        movingRectsRight.push_back(movingRect);
      }
    }

    Uint32 currentTime = SDL_GetTicks();
    if(currentTime - startTime >= 10000) {
      createRectVec(rects, 1);
      startTime = currentTime;
    }

    if(pointsV.size() <= 0){
      createRectVec(pointsV, 3);
    }



    if(pointsV.size() <= 7) {
      canSpawnLives = false;
    } else if(pointsV.size() >= 7){
      canSpawnLives = true;
    }
    Uint32 currentTimePoints = SDL_GetTicks();
    if(canSpawnLives){
      if(currentTimePoints - startTime >= 9000) {
        createRectVec(rects, 1);
        startTime = currentTimePoints;
      }
    }
    if(pressW && !pressS) {
      velY = -8;
    }
    if(pressS && !pressW) {
      velY = 8;
    }
    if(!pressS && !pressW) {
      velY = 0;
    }

    if(pressA && !pressD) {
      velX = -8;
    } 
    if(pressD && !pressA) {
      velX = 8;
    }
    if(!pressD && !pressA){
      velX = 0;
    }
    player.x += velX;
    player.y += velY;
    

    for (auto &rect : movingRectsRight) {
      moveRectRight(&rect, checkWindowCollision, movingRectsRight);
    }

    for (auto &rect : movingRectsLeft) {
      moveRectLeft(&rect, checkWindowCollision, movingRectsLeft);
    }


    if (playerRectCollision(SCREEN_HEIGHT, SCREEN_WIDTH, rects, player)) {
     if(!collisionPlayerLives) {
        lives++;
        checkRectCollisionDelete(SCREEN_HEIGHT, SCREEN_WIDTH, rects, player);
        collisionPlayerLives = true;
      } else {
        collisionPlayerLives = false;
      }
    }

    if (playerRectCollision(SCREEN_HEIGHT, SCREEN_WIDTH, pointsV, player)) {
     if(!collisionPoint) {
        points++;
        checkRectCollisionDelete(SCREEN_HEIGHT, SCREEN_WIDTH, pointsV, player);
        collisionPoint = true;
      } else {
        collisionPoint = false;
      }
    }
// pointsV
    if (checkWindowCollision(SCREEN_HEIGHT, SCREEN_WIDTH, movingRectsRight)) {
      int randomY = distributionY(engine);
      for(int i = 0; i < movingRectsRight.size(); i++) {
        movingRectsRight[i].y = randomY;
      }
    }

    SDL_SetRenderDrawColor(renderer, 1, 7, 15, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 140, 255);

    // if (playerRectCollision(SCREEN_HEIGHT, SCREEN_WIDTH, movingRects, player)) {
    // }
    if (playerRectCollision(SCREEN_HEIGHT, SCREEN_WIDTH, rectsInline, player)) {
      if (!collisionStarted1) {

          lives -= 1;

          collisionStarted1 = true;  
      }
    } else {
      collisionStarted1 = false;
    }
    if (playerRectCollision(SCREEN_HEIGHT, SCREEN_WIDTH, movingRectsLeft, player)) {
      if (!collisionStarted2) {

          lives -= 1;

          collisionStarted2 = true;  
      }
    } else {
      collisionStarted2 = false;
    }
    if (playerRectCollision(SCREEN_HEIGHT, SCREEN_WIDTH, movingRectsRight, player)) {
      if (!collisionStarted3) {
          // This block will execute only when the collision has just started

          lives -= 1;

          collisionStarted3 = true;  // Set the flag to true to indicate that the collision has started
      }
    } else {
      // Reset the flag when there is no collision
      collisionStarted3 = false;
    }

    if(lives == 0) {
      exit(EXIT_SUCCESS);
    }



    SDL_RenderCopy(renderer, backgroundImage, NULL, NULL);
    SDL_RenderDrawLine(renderer, player.bw, player.bw + 60, player.bh, player.bh + 60);

    // Render rectangles
    for (const auto &rect : rects) {
      rect.render(renderer, heartTexture);
    }

    // SDL_SetRenderDrawColor(renderer, 0, 100, 255, 255);

    for (const auto &rect : rectsInline) {
      rect.render(renderer, laserVTexture);
    }

    // SDL_SetRenderDrawColor(renderer, 255, 0, 55, 255);
    //LIVES LIVES
    for (const auto &rect : pointsV) {
      rect.render(renderer, coinTexture);
    }

    // SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);

    for (auto &rect : movingRectsRight) {
      rect.render(renderer, laserTexture);
    }

    // SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);

    for (auto &rect : movingRectsLeft) {
      rect.render(renderer, laserTexture);
    }

    SDL_SetRenderDrawColor(renderer, 100, 25, 255, 255);
    // player.render(renderer);

    printFont(to_string(rects.size()).c_str(), 25, 25, renderer, font, fColor);

    ostringstream livesStream;
    ostringstream livesStreamPoints;

    livesStream << "Lives: " << lives;
    livesStreamPoints << "Points: " << points;

    string livesText = livesStream.str();
    string pointsText = livesStreamPoints.str();
    printFont(livesText.c_str(), SCREEN_WIDTH - 150, 25, renderer, font, fColor);
    printFont(pointsText.c_str(), SCREEN_WIDTH - 450, 25, renderer, font, fColor);

    // Present the renderer
    player.render(renderer, texture);
    
    SDL_RenderPresent(renderer);

    SDL_Delay(16);
  }

  return 0;
}

// SDL_SetRenderDrawColor(renderer, 200, 10, 50, 255);
// SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
// SDL_RenderClear(renderer);
// vector<C_Rect> recTest = {C_Rect (10, 10, 50, 50), C_Rect (25, 25, 50, 50),
// C_Rect (500, 500, 50, 50)}; recTest[0].render(renderer);
// recTest[1].render(renderer);
// recTest[2].render(renderer);

// bool checkRectCollision(int screenHeight, int screenWidth, vector<C_Rect>&
// rects) {
//     int count = 0;

//     for(int i = 0; count < rects.size(); i++){
//         if (rects[count].x <= rects[i].x && rects[count].x + rects[count].w
//         >= rects[i].x
//             && rects[count].y <= rects[i].y && rects[count].y +
//             rects[count].h >= rects[i].y){ return true;
//         }

//         if(i == rects.size()-1){
//             i = 0;
//             count++;
//         }
//     }
//     return false;
// }

// class C_Rect{
//     public:
//         int x, y, w, h;
//             C_Rect(int x_pos, int y_pos, int width, int height)
//             : x(x_pos), y(y_pos), w(width), h(height) {}

//         void render(SDL_Renderer *renderer) const {
//             SDL_Rect r = { x, y, w, h };
//             SDL_RenderDrawRect(renderer, &r);
//             SDL_RenderFillRect(renderer, &r);
//         }

        // case SDLK_r:
        //   reloadRects(rects, renderer, numRects);
        //   break;
        //
        // case SDLK_UP:
        //   rects.push_back(createRectVec(rects, 0)[0]);
        //   numRects++;
        //   cout << "numRects: " << numRects << " rects size: " << rects.size()
        //        << endl;
        //   reloadRects(rects, renderer, numRects);
        //   break;
        //
        // case SDLK_DOWN:
        //   rects.pop_back();
        //   numRects--;
        //   cout << "numRects: " << numRects << " rects size: " << rects.size()
        //        << endl;
        //   reloadRects(rects, renderer, numRects);
        //   break;/ };
