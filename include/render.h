#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

#include "player.h"
#include "world.h"
#include "camera.h"

#define TITLE_FONT_SIZE 64
#define TEXT_FONT_SIZE 28

void render_frame(
    SDL_Renderer *renderer,
    const Player *player,
    const World *world,
    const Camera *camera 
);

void render_game_over(
    SDL_Renderer * renderer,
    TTF_Font *title_font,
    TTF_Font *text_font
);

#endif