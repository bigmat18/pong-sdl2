#include "headers/entity.h"
#include "headers/game.h"
#include "headers/constants.h"
#include <math.h>

void initGame(Game *game){
    game->score[0] = 0;
    game->score[1] = 1;
    
    initPlayer(game, 0);
    initPlayer(game, 1);
    initBall(game);
}

void initPlayer(Game *game, int player){
    game->players[player].positon.x = (int)floorf((SCREEN_WIDTH - PLAYER_WIGTH) * player);
    game->players[player].positon.y = (int)floorf((SCREEN_HEIGTH / 2) - (PLAYER_HEIGTH / 2));
}

void initBall(Game *game){
    game->ball.position.x = (int)floorf(SCREEN_WIDTH / 2);
    game->ball.position.y = (int)floorf(SCREEN_HEIGTH / 2);
}
