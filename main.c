#include "utils.h"
#include "ball.h"
#include "enviroment.h"
#include "player.h"
#include <raylib.h>
#include <hashmap.h>
#include <pthread.h>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    ball* b = init_ball(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,BALL_R);
    player* p1 = init_player(PLAYER_LEFT);
    player* p2 = init_player(PLAYER_RIGHT);
    attach_players(b,p1,p2);

    pthread_t t_ball;
    pthread_t t_p1;
    pthread_t t_p2;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong Game");

    SetTargetFPS(FPS);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    pthread_create(&t_p1,NULL,player_loop_parallel,p2);
    pthread_create(&t_p2,NULL,player_loop_parallel,p1);
    pthread_create(&t_ball,NULL,ball_loop_parallel,b);
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        
            ClearBackground(RAYWHITE);
            draw_ball(b);
            draw_player(p1);
            draw_player(p2);
            
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    pthread_cancel(t_ball);
    pthread_cancel(t_p1);
    pthread_cancel(t_p2);

    destroy_ball(b);
    destroy_player(p1);
    destroy_player(p2);
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
