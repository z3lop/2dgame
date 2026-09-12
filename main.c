#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

typedef struct {
    float x;
    float y;

    float width;
    float height;

    float velocity_x;
    float velocity_y;

    bool double_jump;
    bool on_ground;
} Player;

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;

    bool running;
} Game;

bool game_init(Game *game)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init error: %s\n", SDL_GetError());
        return false;
    }

    game -> window = SDL_CreateWindow(
        "Jump", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        WINDOW_WIDTH, 
        WINDOW_HEIGHT, 
        0
    );

    if (!game->window) {
        printf("Window error: %s\n", SDL_GetError());
        return false;
    }

    game->renderer = SDL_CreateRenderer(
        game->window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!game->renderer) {
        printf("Renderer error: %s\n", SDL_GetError());
        SDL_DestroyWindow(game->window);
        SDL_Quit();
        
        return false;
    }

    game->running = true;
    return true;
}

void handle_input(Game *game, Player *player) 
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            game->running = false;
        }

        if (event.type == SDL_KEYDOWN &&
            event.key.repeat == 0) {

            if (event.key.keysym.sym == SDLK_SPACE) {

                /* normaler Sprung */
                if (player->on_ground) {

                    player->velocity_y = -500.0f;
                    player->on_ground = false;
                }

                /* Double Jump */
                else if (!player->double_jump) {

                    player->velocity_y = -500.0f;
                    player->double_jump = true;
                }
            }
        }
    }
    const Uint8 *keyboard = SDL_GetKeyboardState(NULL);

    player->velocity_x = 0.0f;

    if(keyboard[SDL_SCANCODE_A]) {
        player->velocity_x = -250.0f;
    }

    if(keyboard[SDL_SCANCODE_D]) {
        player->velocity_x = 250.0f;
    }
}

void update_player(Player *player, float dt) 
{
    const float gravity = 1200.0f;
    const float ground_y = 550.0f;

    player->velocity_y += gravity * dt;

    player->x += player->velocity_x * dt;
    player->y += player->velocity_y * dt;

    float player_bottom = player->y + player->height;

    if (player_bottom >= ground_y) {
        player->y = ground_y - player->height;

        player->velocity_y = 0.0f;
        player->on_ground = true;
        player->double_jump = false;
    }

    if (player->x < 0.0f) {
        player->x = 0.0f;
    }

    if (player->x + player->width > WINDOW_WIDTH) {
        player->x = WINDOW_WIDTH - player->width;
    }
}

void render(Game *game, const Player *player)
{
    SDL_SetRenderDrawColor(
        game->renderer,
        30, 30, 40, 255
    );

    SDL_RenderClear(game->renderer);

    SDL_FRect ground = {
        0.0f,
        550.0f,
        WINDOW_WIDTH,
        55.0f
    };

    SDL_SetRenderDrawColor(
        game->renderer, 
        100, 200, 100, 255
    );

    SDL_RenderFillRectF(
        game->renderer,
        &ground
    );

    SDL_FRect player_rect = {
        player->x,
        player->y,
        player->width,
        player->height
    };

    SDL_SetRenderDrawColor(
        game->renderer,
        255, 100, 100, 255
    );

    SDL_RenderFillRectF(
        game->renderer,
        &player_rect
    );


    SDL_RenderPresent(game->renderer);
}

void game_cleanup(Game *game)
{
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);

    SDL_Quit();
}

int main(void)
{
    Game game;

    if (!game_init(&game)) {
        return 1;
    }


    Player player = {
        .x = 375.0f,
        .y = 500.0f,

        .width = 50.0f,
        .height = 50.0f,

        .velocity_x = 0.0f,
        .velocity_y = 0.0f,

        .on_ground = true,
        .double_jump = false
    };


    Uint64 previous_time = SDL_GetPerformanceCounter();

    while (game.running) {

        Uint64 current_time = SDL_GetPerformanceCounter();

        float dt =
            (float)(current_time - previous_time) /
            (float)SDL_GetPerformanceFrequency();

        previous_time = current_time;


        /*
         * Falls das Fenster z.B. im Debugger hängt,
         * soll die Physik nicht plötzlich 3 Sekunden
         * auf einmal berechnen.
         */
        if (dt > 0.05f) {
            dt = 0.05f;
        }


        handle_input(&game, &player);

        update_player(&player, dt);

        render(&game, &player);
    }


    game_cleanup(&game);

    return 0;
}













