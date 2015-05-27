#pragma once

#include "entity_living.h"
#include "stage.h"

#define PROJECTILE_HEALTH 1
#define PROJECTILE_SPEED 100
#define PROJECTILE_HIT_RADIUS 4

typedef struct projectile {
    entity_living_t entity_live;
    int projectile_id;
    uint16_t damage;
} projectile_t;

void projectile_init(projectile_t *projectile,
		     int projectile_id,
		     uint16_t damage,
		     movement_t movement);

void projectile_update(entity_t *entity, stage_t *stage);
