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
    static int diraction; 
    static bool init = false;

    if(!init){
        endPoint = getRandomPosition();
        startPoint = game->ball.position;
        diraction = -1;
        init = true;
    }

    if(!isBallMovmentAllowed(game)) return;
    
    Position newPosition = getBallPosition(game, startPoint, endPoint, diraction);

    // if(hasBallCollided(game, newPosition)){
    //     // Calcolate new possible point
    // }

    game->ball.position.x = newPosition.x;
    game->ball.position.y = newPosition.y;
}


Position getBallPosition(Game *game, Position startPoint, Position endPoint, int diraction) {
    int newXPos;
    int newYPos;

    newXPos = game->ball.position.x + diraction;

    float step1 = (float)(endPoint.y - startPoint.y);
    float step2 = (float)(endPoint.x - startPoint.x);
    float step3 = (float)(newXPos - startPoint.x);
    float step4 = (((step1 / step2) * step3) + (float)(startPoint.y));
    newYPos = (int)floorf(step4);

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

    if(elapsed < GAME_SPEED) return false;
    else{
        oldTime = newTime;
        return true;
    }

}

bool hasBallCollided(Game *game, Position newPosition){
    return true;
}
