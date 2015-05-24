#include <stdio.h>
#include "entiy_living.h"

void entity_living_init(stage_t *stage,
			entity_living_t *entity_live,
			uint16_t health,
		        movement_t movement)
{
  entity_live->health = health;
  entity_init(stage, &entity_live->entity, movement);
}
