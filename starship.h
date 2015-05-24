#pragma once

#include <stdint.h>
#include "entity_living.h"

#define FULL_CHARGE 100

typedef struct starship{
  entity_living_t entity_live;
  uint16_t armor_level;
  uint16_t weaponry_level;
  float charge;
} starship_t;

void starship_init(stage_t *stage,
		   starship_t *starship,
		   uint16_t health,
		   uint16_t armor_level,
		   uint16_t weaponry_level,
		   vec2_t position,
		   vec2_t velocity,
		   vec2_t acceleration);
