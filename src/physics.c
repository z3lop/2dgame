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

static bool physics_resolve_x_collision(
    Player *player,
    const WorldObject *object
)
{
    if (!collision_player_object(player, object)) {
        return false;
    }

    // Bei Kollision Player verschieben
    if (player->velocity_x > 0.0f) {
        player->x = object->x - player->width;

        player->velocity_x = 0.0f;
    }
    else if (player->velocity_x < 0.0f) {
        player->x = object->x + object->width;

        player->velocity_x = 0.0f;
    }

    return true;
}

static YCollision physics_resolve_y_collision(
    Player *player,
    const WorldObject *object
)
{
    if (!collision_player_object(player, object)) {
        // gibt es keine Kollision, checkt er das nächste Objekt
        return Y_COLLISION_NONE;
    }

    // Spieler fällt auf Objekt
    if (player->velocity_y > 0.0f) {
        player->y = object->y - player->height;

        player->velocity_y = 0.0f;
        player->on_ground = true;

        return Y_COLLISION_GROUND;

    } 
    
    // Spieler stößt gegen Objekt
    if (player->velocity_y < 0.0f) {

        player->y =
            object->y + object->height;

        player->velocity_y = 0.0f;
        return Y_COLLISION_CEILING;
    }

    return Y_COLLISION_NONE;
}

static void physics_move_x(
    Player *player,
    const World *world,
    float dt
)
{
    player->x += player->velocity_x * dt;
    bool touch_wall = false;

    // static objects
    for (int i = 0; i < world->object_count; i++) {
        const WorldObject *object = &world->objects[i];

        if (physics_resolve_x_collision(
            player, object
        )) {
            touch_wall = true;
        }

    }

    for (int i = 0; i < world->moving_count; i++) {
        
        // Man kann in keine Wand laufen, auf der man steht
        if (player->riding_platform == i) {
            continue;
        }
        
        const WorldObject *object = &world->moving_objects[i].object;

        if (physics_resolve_x_collision(
            player, object
        )) {
            touch_wall = true;
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

    player->on_ground = false;
    player->riding_platform = -1;

    // statische Objekte
    for (int i = 0; i < world->object_count; i++) {
        const WorldObject *object = &world->objects[i];

        physics_resolve_y_collision(player, object);
    }

    for (int i = 0; i < world->moving_count; i++) {
        const WorldObject *object = &world->moving_objects[i].object;

        YCollision collision = 
            physics_resolve_y_collision(player, object);

        if (collision == Y_COLLISION_GROUND) {
            player->riding_platform = i;
        }
    }

}

static void physics_carry_player(
    Player *player,
    const World *world
)
{
    if (player->riding_platform < 0) {
        return;
    }

    if (player->riding_platform >= world->moving_count) {
        player->riding_platform = -1;
        return;
    }

    const MovingObject *platform = 
        &world->moving_objects[player->riding_platform];

    player->x += platform->delta_x;
    player->y += platform->delta_y;
}

void physics_update_player(
    Player *player,
    const World *world,
    float dt
)
{   
    physics_carry_player(player, world);
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