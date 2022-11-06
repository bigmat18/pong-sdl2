#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "headers/utils.h"

/**
 * ==============================
 * ====== WRAPPER FUNCTION ======
 */

void scc(int code){
    if(code < 0){
        printf("SDL Error: %s", SDL_GetError());
        exit(1);
    }
    return;
}

void *scp(void *ptr){
    if(ptr == NULL){
        printf("SDL Error: %s", SDL_GetError());
        exit(1);
    }
    return ptr;
}
