#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "entity.h"

typedef struct entity_living{
  entity_t entity;
  uint16_t health;
} entity_living_t;

void entity_living_init(entity_living_t *entity_live,
			uint16_t health,
			entity_type_t type,
		        movement_t movement);

void entity_living_update(entity_t *entity, stage_t *stage);
