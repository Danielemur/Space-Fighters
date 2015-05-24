#include <stdio.h>
#include "entiy_living.h"

void entity_living_init(entity_living_t *entity_live,
			uint16_t health,
			entity_type_t type,
		        movement_t movement)
{
  entity_live->health = health;
  entity_init(&entity_live->entity, type, movement);
}
