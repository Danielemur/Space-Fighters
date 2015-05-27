#include <stdio.h>
#include <stdint.h>
#include "entity_living.h"
#include "stage.h"
#include "entity.h"

void entity_living_init(entity_living_t *entity_live,
			uint16_t health,
			entity_type_t type,
		        movement_t movement)
{
    entity_live->health = health;
    entity_init(&entity_live->entity, type, movement);
}

bool entity_living_update(entity_t *entity, stage_t *stage)
{
    entity_living_t *entity_live = (entity_living_t*)entity;
    if (entity_live->health > 0) {
        entity_update(entity, stage);
        return true;
    }
    else {
        stage_remove_entity(stage, entity);
        return false;
    }
}
