#ifndef CONSTANTS_H
#define CONSTANTS_H

/* ====== SIZE ====== */
#define SCREEN_WIDTH        700
#define SCREEN_HEIGTH       600

#define PLAYER_WIGTH        20
#define PLAYER_HEIGTH       80
#define PLAYER_SPEED        40

#define BALL_RADIUS         15
#define BALL_SPEED          0.003

/* ====== COLOR ====== */
#define BACKGROUND_COLOR    0x000000FF
#define PLAYER_COLOR        0x000000FF
#define BALL_COLOR          0xFFFFFFFF
#define SCORE_COLOR         0xFFFFFF00

/* ====== CONVERTER ====== */
#define HEX_COLOR(hex)             \
    ((hex) >> (3 * 8)) & 0xFF,     \
    ((hex) >> (2 * 8)) & 0xFF,     \
    ((hex) >> (1 * 8)) & 0xFF,     \
    ((hex) >> (0 * 8)) & 0xFF

#endif
