#include "../include/physics.h"
#include "../include/collision.h"
#include <SDL2/SDL_rect.h>
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

void world_update_moving_objects(
    World *world,
    float dt
)
{
    for (int i = 0; i < world->moving_count; i++) {
        MovingObject *object = &world->moving_objects[i];

        if (object->point_count <= 0) {
            continue;
        }

        SDL_FPoint target = 
        object->path[object->next_point];
        
        float old_x = object->object.x;
        float old_y = object->object.y;

    
        float dx = (target.x - old_x);
        float dy = (target.y - old_y);
        float distance = 
            sqrtf(dx * dx + dy * dy);

        object->delta_x = 0.0f;
        object->delta_y = 0.0f;
        
        //Ziel Erreicht
        if (distance <= 0.001f) {
            object->object.x = target.x;
            object->object.y = target.y;

            object->next_point++;

            if (object->next_point >= object->point_count) {
                if (object->loop) {
                    object->next_point = 0;
                } else {
                    object->next_point = object->point_count - 1;
                }
            }

            // Ziel für diesen Frame erreicht und wir machen 
            // mit dem nächsten bewegbaren Objekt weiter
            continue;
        } 

        float movement = object->speed * dt;
        // Ziel überschossen
        if (movement >= distance) {
            object->object.x = target.x;
            object->object.y = target.y;

            object->next_point++;

            if (object->next_point >= object->point_count) {
                if (object->loop) {
                    object->next_point = 0;
                } else {
                    object->next_point = object->point_count - 1;
                }
            }

            // Ziel für diesen Frame erreicht und wir machen 
            // mit dem nächsten bewegbaren Objekt weiter
            continue;
        } 

        float direction_x = dx / distance;
        float direction_y = dy / distance;
        
        object->delta_x = direction_x * movement;
        object->delta_y = direction_y * movement;

        object->object.x += object->delta_x;
        object->object.y += object->delta_y;

    }
}