#ifndef ENTITY_H
#define ENTITY_H

typedef enum {
    MOVING_UP,
    MOVING_DOWN,
} PlayerMovment;

/* Define a couple of coordinate on screen */
typedef struct {
    int x;
    int y;
} Position;

/* Define the ball in the game */
typedef struct {
    Position position;
    float speed;
    int diraction;
} Ball;

/* Define a player in the game */
typedef struct {
    Position position;
} Player;

/* Define all element and variable present in game*/
typedef struct {
    Player players[2];
    Ball ball;
    int score[2];
} Game;

#endif
