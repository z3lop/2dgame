#include "../include/world.h"

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

void world_init(World *world)
{
    world->object_count = 0;
    world->width = 3000.0f;
    world->height = 1000.0f;


    world_add_object(
        world, 
        0.0f, 550.0f, 800.0f, 50.0f);

    world_add_object(
        world, 
        200.0f, 430.0f, 200.0f, 30.0f);
    
        /* zweite Plattform */
    world_add_object(
        world,
        500.0f, 350.0f, 180.0f, 30.0f
    );

    /* Wand */
    world_add_object(
        world,
        700.0f, 400.0f, 40.0f, 150.0f
    );
}
