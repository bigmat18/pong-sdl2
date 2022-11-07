#include "entity.h"

#ifndef UTILS_H
#define UTILS_H

/* ====== WRAPPER FUNCTION ====== */
void scc(int code);
void *scp(void *ptr);

/* ====== RANDOM FUNCTION ====== */
int getRandomInt(int max, int min);
Position getRandomPosition();
#endif
