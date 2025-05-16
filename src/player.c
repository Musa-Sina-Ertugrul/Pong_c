#include "player.h"
#include <stdlib.h>
#include <raylib.h>
#include <unistd.h>

player* init_player(PLAYER_TYPE player_type){
    player* p = (player*) malloc(sizeof(player));
    int percent = SCREEN_WIDTH*SCORE_PERCENT/100;
    if (player_type == PLAYER_LEFT){
        p->x = percent + PLAYER_WIDTH;
        p->type = PLAYER_LEFT;
    }else{
        p->x = SCREEN_WIDTH-(percent + PLAYER_WIDTH);
        p->type = PLAYER_RIGHT;
    }
    p->width = PLAYER_WIDTH;
    p->height = PLAYER_HEIGHT;
    p->y = SCREEN_HEIGHT/2;
    p->c = LIME;

    return p;
}

void draw_player(player* p){
    DrawRectangle(p->x,p->y,p->width,p->height,p->c);
}

int destroy_player(player* p){
    free(p);
    return 1;
}

void move_player_left(player* p){
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        int updated_y = p->y - PLAYER_SPEED;
        if (updated_y <= 0) return;
        p->y = updated_y;
    }else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
        int updated_y = p->y + PLAYER_SPEED;
        if (updated_y + PLAYER_HEIGHT >= SCREEN_HEIGHT) return;
        p->y = updated_y;
    }
}

void move_player_right(player* p){
    if (IsKeyDown(KEY_A)){
        int updated_y = p->y - PLAYER_SPEED;
        if (updated_y <= 0) return;
        p->y = updated_y;
    }else if (IsKeyDown(KEY_D)){
        int updated_y = p->y + PLAYER_SPEED;
        if (updated_y + PLAYER_HEIGHT >= SCREEN_HEIGHT) return;
        p->y = updated_y;
    }
}

void move_player(player* p){
    if (p->type == PLAYER_LEFT) move_player_left(p);
    else move_player_right(p);
    usleep(1000);
}

void reset_player(player* p){
    p->y = SCREEN_HEIGHT/2;
}

void* player_loop_parallel(void* p){
    player* p_local = (player*) p;

    while (1)
    {
        move_player(p_local);
    }
    
    return NULL;
}
