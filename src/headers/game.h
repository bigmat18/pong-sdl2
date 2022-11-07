#include "entity.h"
#include <stdbool.h>

#ifndef GAME_H
#define GAME_H

/*
 * =================================
 * ====== INIT FUNCITON ============
 */

/* Init all entity in game */
void initGame(Game *game);

/* Init player number 'player' */
void initPlayer(Game *game, int player);

/* Init ball */
void initBall(Game *game);

/*
 * =================================
 * ====== CHANGE GAME STATUS =======
 */

/* Update player position reference with 'player' */
void updatePlayerPosition(Game *game, int player, PlayerMovment movment);

void updateBallPosition(Game *game, Position nextPoint, int diraction);

bool isBallMovmentAllowed(Game *game);

#endif
