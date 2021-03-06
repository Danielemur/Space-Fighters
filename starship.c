#include <stdio.h>
#include <stdlib.h>
#include "starship.h"
#include "entity_living.h"
#include "player.h"
#include "projectile.h"
#include "stage.h"

void starship_init(starship_t *starship,
		   uint16_t health,
		   uint16_t armor_level,
		   uint16_t weaponry_level,
		   double hit_radius,
		   entity_type_t type,
		   movement_t movement)
{
    starship->armor_level = armor_level;
    starship->weaponry_level = weaponry_level;
    starship->hit_radius = hit_radius;
    starship->charge = FULL_CHARGE;
    entity_living_init(&starship->entity_live, health, type, movement);
}

void starship_fire(starship_t *starship, stage_t *stage)
{
    if (starship->charge > FIRE_DRAIN) {
        entity_t *entity = (entity_t*)starship;
        int projectile_id = -1;
        if (entity->type == PLAYER)
            projectile_id = ((player_t*)starship)->player_id;
        uint16_t damage = 10 * (starship->weaponry_level + 1);
        projectile_t *projectile = malloc(sizeof(projectile_t));
        projectile_init(projectile, projectile_id, damage, (movement_t){entity->movement.position, vec2_scale(entity->movement.orientation, PROJECTILE_SPEED), {0, 0}, entity->movement.orientation});
        stage_add_entity(stage, (entity_t*)projectile);
        starship->charge -= FIRE_DRAIN;
    }
}

bool starship_update(entity_t *entity, stage_t *stage)
{
    starship_t *starship = (starship_t*)entity;
    starship->charge++;
    return entity_living_update(entity, stage);
}
