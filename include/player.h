
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "enviroment.h"
#include <raylib.h>

typedef struct 
{
    int x;
    int y;
    int width;
    int height;
    Color c;
    PLAYER_TYPE type;
} player;

player* init_player(PLAYER_TYPE);
void* player_loop_parallel(void*);
void draw_player(player* p);
int destroy_player(player* p);
void move_player(player* p);
void reset_player(player* p);

#endif