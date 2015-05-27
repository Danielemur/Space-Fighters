#include <stdio.h>
#include "stage.h"
#include "entity.h"
#include "vec2.h"
#include "common.h"

void entity_init(entity_t *entity,
		 entity_type_t type,
		 movement_t movement)
{
    entity->type = type;
    entity->movement = movement;
    entity->last = NULL;
    entity->next = NULL;
}

void entity_update(entity_t *entity, stage_t *stage)
{
    entity->movement.velocity = vec2_add(entity->movement.velocity, vec2_scale(entity->movement.acceleration, 1.0 / (double)FPS));
    entity->movement.position = vec2_add(entity->movement.position, vec2_scale(entity->movement.velocity, 1.0 / (double)FPS));
    if (vec2_mag2(entity->movement.velocity) > 0)
        entity->movement.orientation = vec2_unitize(entity->movement.velocity);
}
