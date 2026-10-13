#ifndef WORLD_H
#define WORLD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../include/config.h"

typedef struct {
    float x;
    float y;
    float width;
    float height;
} WorldObject;

typedef struct {
    WorldObject object;

    float speed;

    SDL_FPoint path[MAX_PATH_POINTS];
    int next_point;

    int point_count;
    bool loop;

    float delta_x;
    float delta_y;

} MovingObject;

typedef struct {
    WorldObject *objects;
    int object_count;
    int object_capacity;

    MovingObject *moving_objects;
    int moving_count;
    int moving_capacity;

    float width;
    float height;

    float death_y;

    /* Lowest world coordinate visible at the bottom of the camera. */
    float camera_bottom;
    
} World;

void world_init(World *world);

void world_add_object(
    World *world,
    float x,
    float y,
    float width,
    float height
);

void world_add_moving_object(
    World *world,
    float x, 
    float y, 
    float width, 
    float height, 
    const SDL_FPoint path[], 
    int next_point,
    int point_count,
    float speed,
    bool loop
);

void world_destroy(World *world);
bool world_allocate(World *world);

#endif
