#pragma once

#include "entity.h"

#define ASTEROID_HIT_RADIUS 10

typedef struct asteroid {
  entity_t entity;
  int tex_id;
} asteroid_t;

void asteroit_init(asteroid_t *asteroid);

void asteroid_update(entity_t *entity, stage_t *stage);
