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

void entity_living_update(entity_living_t *entity_live)
{
  if (entity_live->health <=0)
    stage_remove_entity((entity*)entity_live);
  else
    entity_update(entity_live);
}
