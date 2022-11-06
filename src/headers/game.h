#include "entity.h"

#ifndef GAME_H
#define GAME_H

/* Init all entity in game */
void initGame(Game *game);

/* Init player number 'player' */
void initPlayer(Game *game, int player);

/* Init ball */
void initBall(Game *game);

#endif
