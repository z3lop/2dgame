#include "../include/game.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

static void game_handle_events(Game *game);
static void game_update(Game *game, float dt);
static void game_render(Game *game);

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
    player_init(&game->player);
    world_init(&game->world);

    return true;
}

void game_run(Game *game) 
{
    Uint64 previous_time = SDL_GetPerformanceCounter();

    while (game->running) {

        Uint64 current_time = SDL_GetPerformanceCounter();

        float dt =
            (float)(current_time - previous_time) /
            (float)SDL_GetPerformanceFrequency();

        previous_time = current_time;

        if (dt > 0.05f) {
            dt = 0.05f;
        }

        /*
         * Falls das Fenster z.B. im Debugger hängt,
         * soll die Physik nicht plötzlich 3 Sekunden
         * auf einmal berechnen.
         */
        if (dt > 0.05f) {
            dt = 0.05f;
        }


        game_handle_events(game);

        player_handle_input(&game->player);
        
        game_update(game, dt);
        game_render(game);

    }
}

static void game_handle_events(Game *game) 
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            game->running = false;
        }

        if (event.type == SDL_KEYDOWN &&
            event.key.keysym.sym == SDLK_ESCAPE) {
                
            game->running = false;
        }
        
            player_handle_event(
                &game->player, 
                &event
            );
    }
}

static void game_update(Game *game, float dt) 
{
    physics_update_player(
        &game->player, &game->world, dt);

    if (game->player.on_ground) {
        game->player.double_jump = false;
    }
}

static void game_render_world(Game *game)
{
    SDL_SetRenderDrawColor(
        game->renderer, 
        100, 200, 100, 255
    );

    for (int i = 0; i < game->world.object_count; i++) {
        WorldObject *object = &game->world.objects[i];

        SDL_FRect rect = {
            object->x, 
            object->y,
            object->width,
            object->height
        };

        SDL_RenderFillRectF(game->renderer, &rect);
    }
}

static void game_render(Game *game)
{   
    // Hintergrund
    SDL_SetRenderDrawColor(
        game->renderer,
        30, 30, 40, 255
    );

    // Alten Frame löschen
    SDL_RenderClear(game->renderer);

    game_render_world(game);

    //Player
    player_render(
        &game->player, 
        game->renderer
    );

    SDL_RenderPresent(game->renderer);

}

void game_cleanup(Game *game)
{
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);

    SDL_Quit();
}