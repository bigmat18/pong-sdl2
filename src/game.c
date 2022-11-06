#include "headers/entity.h"
#include "headers/game.h"


void initGame(Game *game){
    game->score[0] = 0;
    game->score[1] = 1;
    
    initPlayer(game, 0);
    initPlayer(game, 1);

    initBall(game);
}

void initPlayer(Game *game, int player){

}

void initBall(Game *game){

}
