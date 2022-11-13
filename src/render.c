#include "libs/render.h"
#include "libs/constants.h"
#include "libs/utils.h"
#include <math.h>
#include <stdbool.h>

/*
 * =================================
 * ====== RENDER GAME ELEMENT ======
 */

void renderGame(SDL_Renderer *renderer, Game *game){
    scc(SDL_SetRenderDrawColor(renderer, HEX_COLOR(BACKGROUND_COLOR)));
    SDL_RenderClear(renderer);

    renderPlayers(renderer, game);
    renderBall(renderer, game);
    renderScore(renderer, game);

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

void renderScore(SDL_Renderer *renderer, Game *game){
    static SDL_Surface *surface;
    static SDL_Texture *texture;
    static bool init = false;
    static int previusScore[2] = {-1,-1};

    if (previusScore[0] == game->players[0].score && previusScore[1] == game->players[1].score)
        return;

    if (!init){
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
    }

    char str[32];
    sprintf(str, "%d - %d", game->players[0].score, game->players[1].score);

    surface = TTF_RenderText_Solid(game->font, str, (SDL_Color){HEX_COLOR(SCORE_COLOR)});

    if (!surface){
        printf("Error: %s\n", TTF_GetError());
        exit(1);
    }

    texture = scp(SDL_CreateTextureFromSurface(renderer, surface));

    int textW = 0;
    int textH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &textW, &textH);
    SDL_Rect textRect = {(int)floorf(SCREEN_WIDTH / 2) - 30, 0, textW, textH};

    SDL_RenderCopy(renderer, texture, NULL, &textRect);
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
