#pragma once

#include <stdint.h>
#include "entity_living.h"

typedef struct starship{
  entity_living_t entity_live;
  uint26_t armor_level;
  float charge_level;
} starship_t;
