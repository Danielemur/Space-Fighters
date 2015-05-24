#pragma once

#include "entity.h"
#include "stage.h"

#define ASTEROID_HIT_RADIUS 10

typedef struct asteroid {
  entity_t entity;
  int tex_id;
} asteroid_t;

void asteroid_init(asteroid_t *asteroid, int tex_id, movement_t movement);

void asteroid_update(entity_t *entity, stage_t *stage);
