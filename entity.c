#include <stdio.h>
#include "entity.h"

void entity_init(stage_t *stage,
		   entity_t *entity,
		 vec2_t position,
		 vec2_t velocity,
		 vec2_t acceleration)
{
  entity->position = position;
  entity->velocity = velocity;
  entity->acceleration = acceleration;
  stage_add_entity(stage, entity);
}


int entity_destroy(entity_t *entity, stage_t *stage)
{

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
