#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include "headers/constants.h"
#include "headers/utils.h"
#include "headers/entity.h"
#include "headers/render.h"
#include "headers/game.h"

int main(void){
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = scp(SDL_CreateWindow("PingPoing", 0, 0, SCREEN_WIDTH, SCREEN_HEIGTH, SDL_WINDOW_RESIZABLE));
    SDL_Renderer *renderer = scp(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));

    bool quit = false;
    Game game = {0};

    initGame(&game);

    while(!quit){
        SDL_Event event;

        if(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT) 
                quit = true;

            switch(event.key.keysym.scancode){
                case SDL_SCANCODE_UP: {
                    updatePlayerPosition(&game, 0, MOVING_UP);
                    break;
                }
                case SDL_SCANCODE_DOWN: {
                    updatePlayerPosition(&game, 0, MOVING_DOWN);
                    break;
                }
                default: {
                    break;
                }
            }
        }
        renderGame(renderer, &game);
    }
    return 0;
}
