#include "../include/world.h"
#include "../include/config.h"
#include <SDL2/SDL_rect.h>
#include <math.h>
#include <stdbool.h>

bool world_allocate(World *world) 
{
    world->object_capacity = MAX_WORLD_OBJECTS;
    world->moving_capacity = MAX_MOVING_OBJECTS;

    world->object_count = 0;
    world->moving_count = 0;

    world->objects = calloc(
        world->object_capacity,
        sizeof *world->objects
    );

    world->moving_objects = calloc(
        world->moving_capacity,
        sizeof *world->moving_objects
    );

    if (!world->objects || !world->moving_objects) {
        free(world->objects);
        free(world->moving_objects);

        world->objects = NULL;
        world->moving_objects = NULL;

        return false;
    }

    return true;
}

void world_destroy(World *world)
{
    free(world->objects);
    free(world->moving_objects);

    world->objects = NULL;
    world->moving_objects = NULL;

    world->object_count = 0;
    world->moving_count = 0;

    world->object_capacity = 0;
    world->moving_capacity = 0;
}

void world_add_object(
    World *world, 
    float x, float y, float width, float height)
{
    if (world->object_count >= world->object_capacity) {
        return;
    }

    WorldObject *object = &world->objects[world->object_count];

    object->x = x;
    object->y = y;
    object->width = width;
    object->height = height;

    world->object_count++;
}

void world_add_moving_object(
    World *world,
    float x, float y, float width, float height,
    const SDL_FPoint path[], int next_point, int point_count, 
    float speed, bool loop
) 
{  
    if (world->moving_count >= world->moving_capacity) {
        return;
    }

    if (point_count <= 0 || point_count > MAX_PATH_POINTS) {
        return;
    }

    if (next_point < 0 || next_point >= point_count) {
        return;
    }

    MovingObject *object = &world->moving_objects[world->moving_count];

    object->object.x = x;
    object->object.y = y;
    object->object.width = width;
    object->object.height = height;

    object->next_point = next_point;
    object->point_count = point_count;
    object->loop = loop;
    object->speed = speed;

    object->delta_x = 0.0f;
    object->delta_y = 0.0f;

    for (int i = 0; i < point_count; i++) {
        object->path[i] = path[i];
    }

    world->moving_count++;
}

void world_init(World *world)
{
    world->object_count = 0;
    world->moving_count = 0;
    world->width = 3000.0f;
    world->height = 1000.0f;
    world->death_y = 1000.0f;


    world_add_object(
        world, 
        1000.0f, 550.0f, 600.0f, 50.0f);

    /* Keep the view above the underside of the ground, even on a fall. */
    world->camera_bottom =
        world->objects[0].y + world->objects[0].height;
    
    //Platform 1
    world_add_object(
        world, 
        200.0f, 430.0f, 200.0f, 30.0f);
    
    /* zweite Plattform */
    world_add_object(
        world,
        500.0f, 350.0f, 180.0f, 30.0f
    );

    /* Wand 0*/
    world_add_object(
        world,
        700.0f, -200.0f, 40.0f, 450.0f
    );

    /* Wand 1*/
    world_add_object(
        world,
        500.0f, -300.0f, 40.0f, 450.0f
    );


    /* Ebene */
    world_add_object(
        world, 
        700.0f, -200.0f, 200.0f, 30.0f);

    SDL_FPoint platform_path[] = {
        { 800.0f, 400.0f },
        { 1200.0f, 400.0f },
        { 1200.0f, 200.0f }
    };

    world_add_moving_object(
        world,

        800.0f, 400.0f,     // Startposition
        150.0f, 30.0f,      // Größe

        platform_path,

        1,                   // nächstes Ziel
        3,                   // Anzahl Punkte

        100.0f,              // Geschwindigkeit
        true                 // Loop
    );

    // add platform which moves in a circle
    SDL_FPoint platform_path2[CIRCLE_POINTS];

    float center_x = 1200.0f;
    float center_y = 50.0f;
    float radius = 350.0f;

    for (int i = 0; i < CIRCLE_POINTS; i++) {
        float angle = 
            ((float) i / CIRCLE_POINTS) * 2.0f * (float)PI;
        
        platform_path2[i].x =
            center_x + cosf(angle) * radius;
        
        platform_path2[i].y = 
            center_y + sinf(angle) * radius;
    }

    world_add_moving_object(
        world,

        1600.0f, 400.0f,
        150.0f, 30.0f,

        platform_path2,

        1, CIRCLE_POINTS,
        100.0f,
        true
    );

    world_add_object(
        world, 
        0.0f, 550.0f, 600.0f, 50.0f);

    world_add_object(
        world, 
        1000.0f, 550.0f, 600.0f, 50.0f);
}
