#ifndef GAME_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "player.h"


typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;

    bool running;
    Player player;
} Game;

bool game_init(Game *game);
void game_run(Game *game);
void game_cleanup(Game *game);

#endif