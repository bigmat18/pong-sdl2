#include "entity.h"

#ifndef UTILS_H
#define UTILS_H

/* ====== WRAPPER FUNCTION ====== */
void scc(int code);
void *scp(void *ptr);

/* ====== RANDOM FUNCTION ====== */
int getRandomInt(int min, int max);
float getRandomFloat(float min, float max);
Position getRandomPosition();

/* ====== MATH FUNCTION ======= */
float getAngularCoefficient(Position point1, Position point2);

#endif
