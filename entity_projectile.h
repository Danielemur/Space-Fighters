#pragma once

#include <stdint.h>
#include "entity.h"

typedef struct entity_projectile{
  entity_t entity;
  uint16_t damage;
} entity_projectile_t;

void entity_update(entity_t *entity);
