
#ifndef __ENV_H__
#define __ENV_H__   

#define SCREEN_HEIGHT 720
#define SCREEN_WIDTH 1280
#define PLAYER_HEIGHT 100
#define PLAYER_WIDTH 20
#define PLAYER_SPEED 1
#define FPS 60
#define SCORE_PERCENT 15
#define BALL_R 20
#define BALL_SPEED 2

typedef enum {
    NO_DIRECTION = 0,
    UP = 1,
    DOWN = 2,
    RIGHT = 4,
    LEFT = 8
} DIRECTION;

typedef enum {
    PLAYER_LEFT=1,
    PLAYER_RIGHT=2,
} PLAYER_TYPE;

#endif