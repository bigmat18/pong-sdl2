#ifndef CONSTANTS_H
#define CONSTANTS_H

/* ====== SIZE ====== */
#define SCREEN_WIDTH        700
#define SCREEN_HEIGTH       600

#define PLAYER_WIGTH        15
#define PLAYER_HEIGTH       60

/* ====== COLOR ====== */
#define BACKGROUND_COLOR    0x000000FF
#define SNAKE_COLOR         0x00FF00FF
#define FOOD_COLOR          0xFF0000FF
#define SCORE_COLOR         0xFFFFFF00

/* ====== CONVERTER ====== */
#define HEX_COLOR(hex)             \
    ((hex) >> (3 * 8)) & 0xFF,     \
    ((hex) >> (2 * 8)) & 0xFF,     \
    ((hex) >> (1 * 8)) & 0xFF,     \
    ((hex) >> (0 * 8)) & 0xFF

#endif
