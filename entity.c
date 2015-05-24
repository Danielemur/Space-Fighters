#include <stdio.h>
#include "entity.h"

void entity_init(entity_t *entity,
		 entity_type_t type,
		 movement_t movement)
{
  entity->type = type;
  entity->movement = movement;
  entity->last = NULL;
  entity->next = NULL;
}

void entity_update(entity_t *entity)
{

}

void entity_set_position(entity_t *entity)
{

}

void entity_set_velocity(entity_t *entity)
{

}

void entity_set_acceleration(entity_t *entity)
{

}
