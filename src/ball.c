#include "ball.h"
#include "utils.h"
#include "player.h"
#include <stdlib.h>
#include <raylib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

void init_ball_direction(ball* b){

    float probility_x = random_f();
    float probility_y = random_f();
    if (probility_x < 0.5f) b->direction_x = RIGHT;
    else b->direction_x = LEFT;
    if (probility_y < 0.5f) b->direction_y = UP;
    else b->direction_y = DOWN;
}

ball* init_ball(int x, int y, int r){
    ball* b = (ball*) malloc(sizeof(ball));
    b->x = x;
    b->y = y;
    b->r = r;
    b->direction_x = NO_DIRECTION;
    b->direction_y = NO_DIRECTION;
    b->players = NULL;
    b->c = MAROON;
    init_ball_direction(b);
    return b;
}

void attach_players(ball* b,player* p1,player* p2){
    player** players = (player**) malloc(2*sizeof(player*));
    players[0] = p1;
    players[1] = p2;
    b->players = players;
}

int is_collide_ball(ball* b,player* p){

    if (p->type & PLAYER_LEFT){
        int p_right_side = p->x + PLAYER_WIDTH;
        int b_left_side = b->x - BALL_R / 2;
        int p_y_start = p->y - PLAYER_HEIGHT;
        int p_y_end = p->y + PLAYER_HEIGHT;
        if(b_left_side < p_right_side && b->y > p_y_start && b->y <p_y_end){
            b->direction_x = RIGHT;
        };
        return 0;
    }else if (p->type & PLAYER_RIGHT){
        int p_left_side = p->x - PLAYER_WIDTH;
        int b_right_side = b->x + BALL_R / 2;
        int p_y_start = p->y - PLAYER_HEIGHT;
        int p_y_end = p->y + PLAYER_HEIGHT;
        if(b_right_side > p_left_side && b->y > p_y_start && b->y <p_y_end){
            b->direction_x = LEFT;
            return 1;
        };
        return 0;
    }else{
        fprintf(stderr,"ERROR: Unkown player type\n");
        return 0;
    }
    return 0;
}

void move_ball(ball* b){
    DIRECTION d_x = b->direction_x;
    DIRECTION d_y = b->direction_y;
    if (d_x == NO_DIRECTION){
        fprintf(stderr , "ERROR: Ball has no direction but tried to move\n");
        return;
    }
    if (d_y == NO_DIRECTION){
        fprintf(stderr , "ERROR: Ball has no direction but tried to move\n");
        return;
    }
    switch (d_x)
    {
    case LEFT:
        {
            int updated_x = b->x - BALL_SPEED;
            if(updated_x<=0) return;
            b->x = updated_x;
            b->direction_x = LEFT;
        }
        break;
    case RIGHT:
        {
            int updated_x = b->x + BALL_SPEED;
            if(updated_x>= SCREEN_WIDTH) return;
            b->x = updated_x; 
            b->direction_x = RIGHT;
        }
        break;
    default:
        fprintf(stderr , "ERROR: Ball has wrong x direction but tried to move direction is : %d\n",d_x);
        return;
    }
    switch (d_y)
    {
    case UP:
        {
            int updated_y = b->y - BALL_SPEED;
            if(updated_y<=0) return;
            b->y = updated_y;
            b->direction_y = UP; 
        }
        break;
    case DOWN:
        {
            int updated_y = b->y + BALL_SPEED;
            if(updated_y>=SCREEN_HEIGHT) return;
            b->y = updated_y;
            b->direction_y = DOWN; 
        }
        break;
    default:
        fprintf(stderr , "ERROR: Ball has wrong y direction but tried to move direction is : %d\n",d_y);
        return;
    }
}

int destroy_ball(ball* b){
    free(b->players);
    free(b);
    return 1;
}

DIRECTION decide_direction_ball_x(ball* b){
    if(b->x - b->r<=0) return RIGHT;
    else if(b->x + b->r>=SCREEN_WIDTH) return LEFT;
    return b->direction_x;
}

DIRECTION decide_direction_ball_y(ball* b){
    if(b->y - b->r<=0) return DOWN;
    else if(b->y + b->r>=SCREEN_HEIGHT) return UP;
    return b->direction_y;
}

void reset_ball(ball* b){
    init_ball_direction(b);
    b->y = SCREEN_HEIGHT/2;
    b->x = SCREEN_WIDTH/2;
}

int is_score(ball* b){
    int percent = SCREEN_WIDTH*SCORE_PERCENT/100;
    if (b->x-b->r < percent || b->x+b->r > SCREEN_WIDTH - percent) return 1;
    return 0;
}

void draw_ball(ball* b){
    DrawCircle(b->x,b->y,(float) b->r,b->c);
}

void* ball_loop_parallel(void* b){
    while (1)
    {
        usleep(10000);
        if (is_score((ball*) b)){
            reset_ball((ball*) b);
            reset_player(((ball*) b)->players[0]);
            reset_player(((ball*) b)->players[1]);
        }
        is_collide_ball((ball*) b,((ball*) b)->players[0]);
        is_collide_ball((ball*) b,((ball*) b)->players[1]);
        ((ball*) b)->direction_x = decide_direction_ball_x((ball*) b);
        ((ball*) b)->direction_y = decide_direction_ball_y((ball*) b);

        move_ball(((ball*) b));
    }
    
    return NULL;
}
