#include "entity.h"
#include <stdbool.h>
#include <SDL2/SDL.h>

#ifndef GAME_H
#define GAME_H

/* ======== INIT FUNCITON ======= */

/** 
 * Init all entity in game 
 * @param game A pointer at the game entity
*/
void initGame(Game *game);


/**
 * Init player
 * @param game A pointer at the game entity
 * @param player The index of player: 0 left player, 1 right player
 */
void initPlayer(Game *game, int player);


/**
 * Init ball
 * @param game A pointer at the game entity
 */
void initBall(Game *game);


/* ====== CHANGE GAME STATUS ======= */

/**
 * Update player position reference with 'player'
 * @param game A pointer at the game entity
 * @param player The index of player: 0 left player, 1 right player
 * @param movment The type of movemnt
 */
void updatePlayerPosition(Game *game, int player, PlayerMovment movment);


/**
 * Update ball position
 * @param game A pointer at the game entity
 * @param end A pointer to bool variable that indicate if game is end or it's in pause state
 */
void moveBall(Game *game, bool *end);


/**
 * Get ball position from two point and current ball position
 * @param game A pointer at the game entity
 * @param startPoint It's a pointer at a Position entity that indicate the start point to calculate
 *                   the straight line
 * @param endPoint It's a pointer at a Position entity that indicate the end point to calculate
 *                   the straight line
 */
Position getBallPosition(Game *game, Position *startPoint, Position *endPoint);


/**
 * Update ball movment chainging the start and end points from le collided coordinates
 * @param game A pointer at the game entity
 * @param startPoint It's a pointer at a Position entity that indicate the start point to calculate
 *                   the straight line
 * @param endPoint It's a pointer at a Position entity that indicate the end point to calculate
 *                   the straight line
 * @param collidedCoordinates It's a pointer at a Position entity that indicate where ball impact
 */
void updateBallMovment(Game *game, Position *startPoint, Position *endPoint, Position *collidedCoordinates);


/**
 * Update ball diraction to mov it left->right or right->left
 * @param game A pointer at the game entity
 * @param collidedCoordinates It's a pointer at a Position entity that indicate where ball impact
 * @param m It's a angular coefficent
 */
void updateBallDiraction(Game *game, Position *collidedCoordinates, float m);


/**
 * Check if movment is allowed calculating the elapsed time
 * @param game A pointer at the game entity
 * @return return true if ball movment is allowed, false else
 */
bool isBallMovmentAllowed(Game *game);


/**
 * Get the coordinates where ball collided
 * @param game A pointer at the game entity
 * @return return a pointer to collided coordinates, NULL if pointer as not collided, a pointer with (-1,-1) if collided
 *         with a player
 */
Position* getBallCollidedCoordinates(Game *game);


/**
 * Reset ball in the center of windows when a player do a point
 * @param game A pointer at the game entity
 */
void resetBall(Game *game);

#endif
