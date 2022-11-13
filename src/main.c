#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL_ttf.h>

#include "libs/constants.h"
#include "libs/utils.h"
#include "libs/entity.h"
#include "libs/render.h"
#include "libs/game.h"

int main(void){
    srand(time(NULL));

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = scp(SDL_CreateWindow("PingPoing", 0, 0, SCREEN_WIDTH, SCREEN_HEIGTH, SDL_WINDOW_RESIZABLE));
    SDL_Renderer *renderer = scp(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));

    bool quit = false;
    bool pause = true;
    Game game = {0};

    TTF_Init();
    char *fontPath = "Aller_Rg.ttf";
    TTF_Font *font = TTF_OpenFont(fontPath, 30);
    if (!font) printf("Error loading font '%s': %s\n", fontPath, TTF_GetError());

    game.font = font;

    initGame(&game);

    while(!quit){
        SDL_Event event;

        if(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT) 
                quit = true;

            switch(event.key.keysym.scancode){
                case SDL_SCANCODE_UP: {
                    updatePlayerPosition(&game, 1, MOVING_UP);
                    break;
                }
                case SDL_SCANCODE_DOWN: {
                    updatePlayerPosition(&game, 1, MOVING_DOWN);
                    break;
                }
                case SDL_SCANCODE_W: {
                    updatePlayerPosition(&game, 0, MOVING_UP);
                    break;
                }
                case SDL_SCANCODE_S: {
                    updatePlayerPosition(&game, 0, MOVING_DOWN);
                    break;
                }
                case SDL_SCANCODE_SPACE: {
                    pause = false;
                    break;
                }
                case SDL_SCANCODE_B: {
                    pause = true;
                    break;
                }
                default: {
                    break;
                }
            }
        }
        if(!pause) moveBall(&game, &pause);
        renderGame(renderer, &game);
    }
    moveBall(&game, &quit);
    return 0;
}
