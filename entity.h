#pragma once

#include "vec2.h"
#include "common.h"

#define ORIGIN {0,0}
#define FPS 15
#define ENTITY_TYPE_NUMBER 6

typedef struct stage stage_t;

typedef enum {
    PLAYER = 0, ENEMY, PROJECTILE, POWERUP, UPGRADE, ASTEROID
} entity_type_t;

typedef struct movement {
    vec2_t position;
    vec2_t velocity;
    vec2_t acceleration;
    vec2_t orientation;
} movement_t;

typedef struct entity {
    movement_t movement;
    entity_type_t type;
    struct entity *last;
    struct entity *next;
    void (*update)(struct entity *entity, stage_t *stage);
} entity_t;

void entity_init(entity_t *entity,
		 entity_type_t type,
		 movement_t movement);

void entity_update(entity_t *entity, stage_t *stage);
