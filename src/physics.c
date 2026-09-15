#include "../include/physics.h"
#include "../include/collision.h"
#include <stdbool.h>

#define PLAYER_GRAVITY 1200.0f
#define WALL_SLIDE_SPEED 240.0f

static void physics_apply_gravity(Player *player, float dt)
{
    player->velocity_y += PLAYER_GRAVITY * dt;
}

static void physics_move_x(
    Player *player,
    const World *world,
    float dt
)
{
    player->x += player->velocity_x * dt;
    bool touch_wall = false;

    for (int i = 0; i < world->object_count; i++) {
        const WorldObject *object = &world->objects[i];

        if (!collision_player_object(
            player, 
            object
        )) {
            // gibt es keine Kollision, checkt er das nächste Objekt
            continue;
        }

        touch_wall = true;

        // Bei Kollision Player verschieben
        if (player->velocity_x > 0.0f) {
            player->x = object->x - player->width;

            player->velocity_x = 0.0f;
        }
        else if (player->velocity_x < 0.0f) {
            player->x = object->x + object->width;

            player->velocity_x = 0.0f;
        }

    }
    
    player->wall_slide = touch_wall && !
                         player->on_ground && 
                         player->velocity_y > 0.0f;

    if (player->wall_slide) {
        player->double_jump = false;
    }
    
    if (collision_player_left(player)) {
        player->x = 0.0f;
        player->velocity_x = 0.0f;
    }
}

static void physics_limit_wall_slide(Player *player)
{
    if (player->wall_slide && player->velocity_y > WALL_SLIDE_SPEED) {
        player->velocity_y = WALL_SLIDE_SPEED;
    }
}

static void physics_move_y(
    Player *player,
    const World *world,
    float dt
)
{
    player->y += player->velocity_y * dt;

    for (int i = 0; i < world->object_count; i++) {
        const WorldObject *object = &world->objects[i];

        if (!collision_player_object(
            player, object
        )) {
            // gibt es keine Kollision, checkt er das nächste Objekt
            continue;
        }
        // Bei Kollision Player verschieben
        if (player->velocity_y > 0.0f) {
            player->y = object->y - player->height;

            player->velocity_y = 0.0f;
            player->on_ground = true;
        } else if (player->velocity_y < 0.0f) {

            player->y =
                object->y + object->height;

            player->velocity_y = 0.0f;
        }

    }
}


void physics_update_player(
    Player *player,
    const World *world,
    float dt
)
{
    physics_apply_gravity(player, dt);
    physics_move_x(player, world, dt);
    physics_limit_wall_slide(player);
    physics_move_y(player, world, dt);
}