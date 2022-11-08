#include "headers/entity.h"
#include "headers/game.h"
#include "headers/constants.h"
#include "headers/utils.h"

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


void moveBall(Game *game){
    static Position endPoint;
    static Position startPoint;
    static bool init = false;

    if(!init){
        endPoint.x = (int)floorf(getRandomFloat(-20, 20));
        endPoint.y = (int)floorf(getRandomFloat(-20, 20));
        startPoint = game->ball.position;
        init = true;
    }

    if(!isBallMovmentAllowed(game)) return;
    

    if(hasBallCollided(game)){

        float m = getAngularCoefficient(startPoint, endPoint);
        float grad = atanf(m) * (180 / M_PI);

        float newM = getRandomFloat(grad - 20, grad + 20) * (M_PI / 180);

        int x = (int)floorf(game->ball.position.x + (cosf(newM) * BALL_RADIUS));
        int y = (int)floorf(game->ball.position.y + (sinf(newM) * BALL_RADIUS));

        startPoint = game->ball.position;
        endPoint.x = x;
        endPoint.y = y;
    }

    Position newPosition = getBallPosition(game, startPoint, endPoint);

    game->ball.position.x = newPosition.x;
    game->ball.position.y = newPosition.y;
}


Position getBallPosition(Game *game, Position startPoint, Position endPoint) {
    int newXPos;
    int newYPos;

    newXPos = game->ball.position.x + game->ball.diraction;

    newYPos = (int)floorf((getAngularCoefficient(startPoint, endPoint) * (float)(newXPos - startPoint.x)) + (float)(startPoint.y));
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

bool hasBallCollided(Game *game){

    for(int i=0; i<360; i++){
       int x = (game->ball.position.x + (cos(i * (M_PI / 180)) * BALL_RADIUS));
       int y = (game->ball.position.y + (sin(i * (M_PI / 180)) * BALL_RADIUS));

       if (x == SCREEN_WIDTH || x == 0) {
            game->ball.diraction *= -1;
            return true;
       } else if (y == 0 || y == SCREEN_HEIGTH) return true;
       
    }

    return false;
}

