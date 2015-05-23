#pragma once

#include "vec2.h"
#include "stage.h"

typedef struct entity{
  struct entity *last;
  vec2_t position;
  vec2_t velocity;
  vec2_t acceleration;
  struct entity *next;
} entity_t;

int entity_create(stage_t *stage);

int entity_destroy(entity_t *entity, stage_t *stage);

void entity_update(entity_t *entity);

void entity_set_position(entity_t *entity);

void entity_set_velocity(entity_t *entity);

void entity_set_acceleration(entity_t *entity);
