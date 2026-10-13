#ifndef LIGHTING_H
#define LIGHTING_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <stdbool.h>
#include "camera.h"

typedef struct {
    float x,y;
    float radius;
    float intensity;
    SDL_Color color;
} LightSource;

typedef struct {
    SDL_Texture *map;
    SDL_Texture *radial;
    int width, height;
    Uint8 ambient;
} Lighting;

bool lighting_init(
    Lighting *lighting,
    SDL_Renderer *renderer,
    int width, int height,
    Uint8 ambient
);

void lighting_destroy(Lighting *lighting);

bool lighting_apply(
    Lighting *lighting,
    SDL_Renderer *renderer,
    const Camera *camera,
    const LightSource lights[],
    int light_count
);

#endif