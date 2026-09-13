#ifndef WORLD_H
#define WORLD_H

#define MAX_WORLD_OBJECTS 128

typedef struct {
    float x;
    float y;
    float width;
    float height;
} WorldObject;

typedef struct {
    WorldObject objects[MAX_WORLD_OBJECTS];
    int object_count;

    float width;
    float height;
    
} World;

void world_init(World *world);

void world_add_object(
    World *world,
    float x,
    float y,
    float width,
    float height
);

#endif

