#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

#include "player.h"
#include "world.h"
#include "camera.h"

void render_frame(
    SDL_Renderer *renderer,
    const Player *player,
    const World *world,
    const Camera *camera,
    TTF_Font *font,
    int fps
);

void render_game_over(
    SDL_Renderer * renderer,
    TTF_Font *title_font,
    TTF_Font *text_font
);

void render_text(
    SDL_Renderer *renderer,
    TTF_Font *font, 
    const char *text,
    float x,
    float y
);

#endif