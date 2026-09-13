#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

#include "player.h"
#include "world.h"
#include "physics.h"
#include "config.h"


typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;

    bool running;
    Player player;
    World world;
} Game;

bool game_init(Game *game);
void game_run(Game *game);
void game_cleanup(Game *game);

#endif