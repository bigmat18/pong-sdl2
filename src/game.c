#include "libs/entity.h"
#include "libs/game.h"
#include "libs/constants.h"
#include "libs/utils.h"

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

/*
 * =================================
 * ====== INIT FUNCITON ============
 */

void initGame(Game *game){
    game->score[0] = 0;
    game->score[1] = 1;
    
    initPlayer(game, 0);
    initPlayer(game, 1);
    initBall(game);
}

void initPlayer(Game *game, int player){
    game->players[player].position.x = (int)floorf((SCREEN_WIDTH - PLAYER_WIGTH) * player);
    game->players[player].position.y = (int)floorf((SCREEN_HEIGTH / 2) - (PLAYER_HEIGTH / 2));
}

void initBall(Game *game){
    game->ball.position.x = (int)floorf(SCREEN_WIDTH / 2);
    game->ball.position.y = (int)floorf(SCREEN_HEIGTH / 2);
    game->ball.speed = BALL_SPEED;
    game->ball.diraction = -1;
}

/*
 * =================================
 * ====== CHANGE GAME STATUS =======
 */

void updatePlayerPosition(Game *game, int player, PlayerMovment movment){
    switch(movment){
        case MOVING_UP: {
            if (game->players[player].position.y - PLAYER_SPEED >= 0)
                game->players[player].position.y -= PLAYER_SPEED;
            else if (game->players[player].position.y != 0)
                game->players[player].position.y -= game->players[player].position.y;
            break;
        }
        case MOVING_DOWN: {
            if (game->players[player].position.y + PLAYER_SPEED <= (SCREEN_HEIGTH - PLAYER_HEIGTH))
                game->players[player].position.y += PLAYER_SPEED;
            else if (game->players[player].position.y != (SCREEN_HEIGTH - PLAYER_HEIGTH))
                game->players[player].position.y += ((SCREEN_HEIGTH - game->players[player].position.y) - PLAYER_HEIGTH);
            break;
        }
    }
}


void moveBall(Game *game, bool *end){
    static Position *endPoint;
    static Position *startPoint;
    static bool init = false;
    static bool activeCollision = true;

    if(*end){
        free(startPoint);
        free(endPoint);
        return;
    }

    if(!init){
        startPoint = malloc(sizeof(Position));
        endPoint = malloc(sizeof(Position));
        endPoint->x = 0;
        endPoint->y = getRandomInt(0, SCREEN_HEIGTH);
        startPoint->x = game->ball.position.x;
        startPoint->y = game->ball.position.y;
        init = true;
    }

    if(!isBallMovmentAllowed(game)) return;

    Position *collidedCoordinates = getBallCollidedCoordinates(game);

    if (collidedCoordinates != NULL && collidedCoordinates->x == -1){
        resetBall(game);
        free(startPoint);
        free(endPoint);
        free(collidedCoordinates);
        init = false;
        *end = true;
        return;
    }

    if(collidedCoordinates != NULL && activeCollision){
        updateBallMovment(game, startPoint, endPoint);
        updateBallDiraction(game, collidedCoordinates, getAngularCoefficient(startPoint, endPoint));
        activeCollision = false;

    } else if (!activeCollision && collidedCoordinates == NULL) activeCollision = true;

    game->ball.position = getBallPosition(game, startPoint, endPoint);
    free(collidedCoordinates);
}


void updateBallMovment(Game *game, Position *startPoint, Position *endPoint){
    startPoint->x = game->ball.position.x;
    startPoint->y = game->ball.position.y;

    int x;

    do x = getRandomInt((int)floorf(SCREEN_WIDTH / 2) - 150, (int)floorf(SCREEN_WIDTH / 2) + 150);
    while(x == startPoint->x);

    endPoint->x = x;
    endPoint->y = getRandomInt((int)floorf(SCREEN_HEIGTH / 2) - 150, (int)floorf(SCREEN_HEIGTH / 2) + 150);
}


void updateBallDiraction(Game *game, Position *collidedCoordinates, float m){

    if (collidedCoordinates->y == 0){
        if (m > 0)
            game->ball.diraction = 1;
        else
            game->ball.diraction = -1;
    }else if (collidedCoordinates->y == SCREEN_HEIGTH){
        if (m > 0)
            game->ball.diraction = -1;
        else
            game->ball.diraction = 1;
    }else
        game->ball.diraction *= -1;
}


Position getBallPosition(Game *game, Position *startPoint, Position *endPoint) {
    int newXPos;
    int newYPos;

    newXPos = game->ball.position.x + game->ball.diraction;

    newYPos = (int)floorf((getAngularCoefficient(startPoint, endPoint) * (float)(newXPos - startPoint->x)) + (float)(startPoint->y));

    if(newYPos < 0) newYPos = 0;
    else if(newYPos > SCREEN_HEIGTH) newYPos = SCREEN_HEIGTH; 

    return (Position){newXPos, newYPos};
}


bool isBallMovmentAllowed(Game *game){

    static struct timeval oldTime = {0};
    static struct timeval newTime = {0};
    static bool init = false;
    double elapsed = -1;

    if(!init){
        init = true;
        gettimeofday(&oldTime, NULL);
        return false;
    }

    gettimeofday(&newTime, NULL);
    elapsed = (double)(newTime.tv_usec - oldTime.tv_usec) / 1000000 +
              (double)(newTime.tv_sec - oldTime.tv_sec);

    if(elapsed < BALL_SPEED) return false;
    else{
        oldTime = newTime;
        return true;
    }
}


Position* getBallCollidedCoordinates(Game *game){

    for(int i=0; i<360; i+=90){
       int x = (game->ball.position.x + (cos(i * (M_PI / 180)) * BALL_RADIUS));
       int y = (game->ball.position.y + (sin(i * (M_PI / 180)) * BALL_RADIUS));

       if ((y == 0 || y == SCREEN_HEIGTH) ||
           ((x <= PLAYER_WIGTH && y >= game->players[0].position.y && y <= game->players[0].position.y + PLAYER_HEIGTH) ||
            (x >= (SCREEN_WIDTH - PLAYER_WIGTH) && y >= game->players[1].position.y && y <= game->players[1].position.y + PLAYER_HEIGTH)))
       {
           Position *newPos = malloc(sizeof(Position));
           newPos->x = x;
           newPos->y = y;
           return newPos;
       }

       if(x == 0 || x == SCREEN_WIDTH){
           Position *newPos = malloc(sizeof(Position));
           newPos->x = -1;
           newPos->y = -1;
           return newPos;
       }
    }

    return NULL;
}

void resetBall(Game *game){
    game->ball.position.x = (int)floorf(SCREEN_WIDTH / 2);
    game->ball.position.y = (int)floorf(SCREEN_HEIGTH / 2);
    game->ball.diraction = -1;
}
