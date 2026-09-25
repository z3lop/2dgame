#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#include "player.h"
#include "world.h"
#include "physics.h"
#include "config.h"
#include "camera.h"
#include "render.h"

typedef enum {
    GAME_STATE_PLAYING,
    GAME_STATE_GAME_OVER
} GameState;


typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *title_font;
    TTF_Font *text_font;

    bool running;
    GameState state;

    Player player;
    World world;
    Camera camera;
} Game;

bool game_init(Game *game);
void game_run(Game *game);
void game_cleanup(Game *game);
void render_text(
    SDL_Renderer *renderer,
    TTF_Font *font, 
    const char *text,
    float x,
    float y
);

#endif