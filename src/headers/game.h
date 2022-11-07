#include "entity.h"

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

#endif
