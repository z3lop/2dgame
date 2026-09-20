#include "../include/world.h"
#include <SDL2/SDL_rect.h>
#include <stdbool.h>

void world_add_object(
    World *world, 
    float x, float y, float width, float height)
{
    if (world->object_count >= MAX_WORLD_OBJECTS) {
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
    if (world->moving_count >= MAX_MOVING_OBJECTS) {
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


    world_add_object(
        world, 
        0.0f, 550.0f, 600.0f, 50.0f);

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
        700.0f, 50.0f, 40.0f, 200.0f
    );

    /* Wand 1*/
    world_add_object(
        world,
        500.0f, -100.0f, 40.0f, 200.0f
    );

    /* Wand 2*/
    world_add_object(
        world,
        700.0f, -250.0f, 40.0f, 200.0f
    );

        /* Wand 3*/
    world_add_object(
        world,
        500.0f, -400.0f, 40.0f, 200.0f
    );

    /* Ebene */
    world_add_object(
        world, 
        700.0f, -400.0f, 200.0f, 30.0f);

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

}
