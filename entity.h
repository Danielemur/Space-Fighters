#pragma once

#include "vec2.h"
#include "stage.h"

#define ORIGIN {0,0}
#define DEFAULT_MOVEMENT {{0, 0}, {0, 0}, {0, 0}}

typedef struct movement {
  vec2_t position;
  vec2_t velocity;
  vec2_t acceleration;
} movement_t;

typedef struct entity {
  movement_t movement;
  struct entity *last;
  struct entity *next;
} entity_t;

void entity_init(stage_t *stage,
		   entity_t *entity,
		 movement_t movement);

int entity_destroy(entity_t *entity, stage_t *stage);

void entity_update(entity_t *entity);

void entity_set_position(entity_t *entity);

void entity_set_velocity(entity_t *entity);

void entity_set_acceleration(entity_t *entity);
