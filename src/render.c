#include "headers/render.h"
#include "headers/constants.h"
#include "headers/utils.h"
#include <math.h>

/*
 * =================================
 * ====== RENDER GAME ELEMENT ======
 */

void renderGame(SDL_Renderer *renderer, Game *game){
    scc(SDL_SetRenderDrawColor(renderer, HEX_COLOR(BACKGROUND_COLOR)));
    SDL_RenderClear(renderer);

    renderPlayers(renderer, game);
    renderBall(renderer, game);

    SDL_RenderPresent(renderer);
}

void renderPlayers(SDL_Renderer *renderer, Game *game){
    SDL_Color color = {HEX_COLOR(PLAYER_COLOR)};
    renderSquare(renderer, &game->players[0].position, PLAYER_WIGTH, PLAYER_HEIGTH, color);
    renderSquare(renderer, &game->players[1].position, PLAYER_WIGTH, PLAYER_HEIGTH, color);
}

void renderBall(SDL_Renderer *renderer, Game *game){
    renderCircle(renderer, 
                &game->ball.position, 
                BALL_RADIUS, 
                (SDL_Color){HEX_COLOR(BALL_COLOR)});
}

/*
 * =================================
 * ====== GEMETRY RENDER ===========
 */

void renderSquare(SDL_Renderer *renderer, Position *position, int width, int heigth, SDL_Color color){
    scc(SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a));
    SDL_Rect rect = {position->x,position->y,width,heigth};
    scc(SDL_RenderFillRect(renderer,&rect));
}

void renderCircle(SDL_Renderer *renderer, Position *position, int radius, SDL_Color color){
    scc(SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a));
    
    for(int i=0; i<180; i++){
        SDL_RenderDrawLineF(renderer,
                            (float)(position->x - (cos(i * (M_PI / 180)) * radius)),
                            (float)(position->y - (sin(i * (M_PI / 180)) * radius)),
                            (float)(position->x + (cos(i * (M_PI / 180)) * radius)),
                            (float)(position->y + (sin(i * (M_PI / 180)) * radius)));
    }

}
