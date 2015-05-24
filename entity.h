#pragma once

#include "vec2.h"
#include "stage.h"

#define ORIGIN {0,0}
#define DEFAULT_MOVEMENT {{0, 0}, {0, 0}, {0, 0}}
#define ENTITY_TYPE_NUMBER 6

typedef enum {
  PLAYER, ENEMY, PROJECTILE, POWERUP, UPGRADE, ASTEROID
} entity_type_t;

typedef struct movement {
  vec2_t position;
  vec2_t velocity;
  vec2_t acceleration;
} movement_t;

typedef struct entity {
  movement_t movement;
  entity_type_t type;
  struct entity *last;
  struct entity *next;
} entity_t;

void entity_init(entity_t *entity,
		 entity_type_t type,
		 movement_t movement);

void entity_update(entity_t *entity);

void entity_set_position(entity_t *entity);

void entity_set_velocity(entity_t *entity);

void entity_set_acceleration(entity_t *entity);
