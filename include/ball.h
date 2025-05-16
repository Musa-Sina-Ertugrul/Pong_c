
#ifndef __BALL_H__
#define __BALL_H__

#include "enviroment.h"
#include "player.h"
#include <raylib.h>

typedef struct {

    int x;
    int y;
    int r;
    DIRECTION direction_x;
    DIRECTION direction_y;
    player** players;
    Color c;

} ball;

ball* init_ball(int x, int y, int r);
void attach_players(ball* b,player* p1,player* p2);
void init_ball_direction(ball*);
void* ball_loop_parallel(void*);
void move_ball(ball* b);
int is_collide_ball(ball* b,player* p);
int destroy_ball(ball* b);
DIRECTION decide_direction_ball_x(ball* b);
DIRECTION decide_direction_ball_y(ball* b);
void reset_ball(ball* b);
int is_score(ball* b);
void draw_ball(ball* b);

#endif  