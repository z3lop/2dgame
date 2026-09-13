#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>

#include "player.h"
#include "world.h"
#include "camera.h"

void render_frame(
    SDL_Renderer *renderer,
    const Player *player,
    const World *world,
    const Camera *camera 
);

#endif