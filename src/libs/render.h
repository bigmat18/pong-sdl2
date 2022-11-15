#include <SDL2/SDL.h>
#include "entity.h"

#ifndef RENDER_H
#define RENDER_H

/* ====== RENDER GAME ELEMENT ====== */

/* Render all element on screen */
void renderGame(SDL_Renderer *renderer, Game *game);

/* Render a player */
void renderPlayers(SDL_Renderer *renderer, Game *game);

/* Render the game ball*/
void renderBall(SDL_Renderer *renderer, Game *game);

void renderScore(SDL_Renderer *renderer, Game *game);


/* ====== GEMETRY RENDER ====== */

/* Render a generic square */
void renderSquare(SDL_Renderer *renderer, Position *position, int width, int heigth, SDL_Color color);

/* Render a generic circle */
void renderCircle(SDL_Renderer *renderer, Position *position, int radius, SDL_Color color);
#endif
