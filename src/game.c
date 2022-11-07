#include "headers/entity.h"
#include "headers/game.h"
#include "headers/constants.h"
#include <SDL2/SDL.h>
#include <math.h>

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
