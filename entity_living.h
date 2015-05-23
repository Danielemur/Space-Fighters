#pragma once

#include <stdint.h>
#include "entity.h"

typedef struct entity_living{
  entity_t entity;
  uint16_t health;
} entity_living_t;

void take_damage(entity_living_t *entity_live);
