#include <stdio.h>
#include <SDL.h>
#include "./constants.h"

int game_is_running = FALSE;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int last_frame_time = 0;

// prototype for pong!
struct ball {
    float x;
    float y;
    float width;
    float height;
} ball;

int initialize_window(void)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "Error initializing SDL.\n");
        return FALSE;
    }
    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS
    );
    if (!window)
    {
        fprintf(stderr, "Error creating SDL Window.\n");
        return FALSE;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) 
    {
        fprintf(stderr, "Error creating SDL renderer.\n");
        return FALSE;
    }
     
    return TRUE;
}

void process_input()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        game_is_running = FALSE;
        break;
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            game_is_running = FALSE;
            break;
        case SDLK_LEFT:
            printf("Left key was pressed.\n ");
            ball.x -= 10 * delta_time;
            break;
        case SDLK_RIGHT:
            printf("Right key was pressed.\n ");
            ball.x += 10 * delta_time;
            break;
        case SDLK_UP:
            printf("Up key was pressed.\n ");
            ball.y += 10 * delta_time;
            break;
        case SDLK_DOWN:
            printf("Down key was pressed.\n ");
            ball.y -= 10 * delta_time;
            break;
        }
    }
}

void setup()
{
    ball.x = 20;
    ball.y = 20;
    ball.width = 15;
    ball.height = 15;
}

void update()
{
    //while (!SDL_TICKS_PASSED(SDL_GetTicks(), last_frame_time + FRAME_TARGET_TIME));

    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
    {
        SDL_Delay(time_to_wait);
    }

    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;

    last_frame_time = SDL_GetTicks();


}

void render()
{
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_RenderClear(renderer);

    SDL_Rect ball_rect = { 
        (int)ball.x, 
        (int)ball.y, 
        (int)ball.width, 
        (int)ball.height 
    };

    SDL_SetRenderDrawColor(renderer, 12, 100, 200, 255); 
    SDL_RenderFillRect(renderer, &ball_rect);

    SDL_RenderPresent(renderer);
}

void destroy_window()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* args[])
{
    game_is_running = initialize_window();

    setup();

    while (game_is_running)
    {
        process_input();
        update();
        render();
    }

    destroy_window();

    return 0;
}
