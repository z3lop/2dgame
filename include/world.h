#ifndef WORLD_H
#define WORLD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <stdbool.h>

#define MAX_WORLD_OBJECTS 128
#define MAX_MOVING_OBJECTS 128
#define MAX_PATH_POINTS 64

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
    WorldObject objects[MAX_WORLD_OBJECTS];
    int object_count;

    MovingObject moving_objects[MAX_MOVING_OBJECTS];
    int moving_count;

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

#endif
