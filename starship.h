#pragma once

#include <stdint.h>
#include "entity_living.h"

#define FULL_CHARGE 100
#define FIRE_DRAIN 20

typedef struct starship{
  entity_living_t entity_live;
  uint16_t armor_level;
  uint16_t weaponry_level;
  float charge;
} starship_t;

void starship_init(starship_t *starship,
		   uint16_t health,
		   uint16_t armor_level,
		   uint16_t weaponry_level,
		   entity_type_t type,
		   movement_t movement);

void starship_fire(starship_t *starship, uint16_t damage);
