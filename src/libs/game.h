#include "entity.h"
#include <stdbool.h>
#include <SDL2/SDL.h>

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

void moveBall(Game *game, bool *end);

Position getBallPosition(Game *game, Position *startPoint, Position *endPoint);

void updateBallMovment(Game *game, Position *startPoint, Position *endPoint, Position *collidedCoordinates);

void updateBallDiraction(Game *game, Position *collidedCoordinates, float m);

bool isBallMovmentAllowed(Game *game);

Position* getBallCollidedCoordinates(Game *game);

void resetBall(Game *game);

#endif
