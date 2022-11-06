#include "headers/render.h"
#include "headers/constants.h"
#include "headers/utils.h"

/*
 * =================================
 * ====== RENDER GAME ELEMENT ======
 */

void renderGame(SDL_Renderer *renderer, Game *game){
    scc(SDL_SetRenderDrawColor(renderer, HEX_COLOR(BACKGROUND_COLOR)));
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void renderPlayer(SDL_Renderer *renderer, Game *game, int player){

}

void renderBall(SDL_Renderer *renderer, Game *game){

}

/*
 * =================================
 * ====== GEMETRY RENDER ===========
 */

void renderSquare(SDL_Renderer *renderer, Position *position, int width, int heigth, SDL_Color color){

}

void renderCircle(SDL_Renderer *renderer, Position *position, int radius, SDL_Color color){
    
}
