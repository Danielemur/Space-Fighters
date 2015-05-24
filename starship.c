#include <stdio.h>
#include "starship.h"

void starship_init(starship_t *starship,
		   uint16_t health,
		   uint16_t armor_level,
		   entity_type_t type,
		   double hit_radius,
		   movement_t movement)
{
  starship->armor_level = armor_level;
  starship->weaponry_level = weaponry_level;
  starship->hit_radius = hit_radius;
  starship->charge = FULL_CHARGE;
  entity_living_init(&starship->entity_live, health, type, movement);
}

void starship_fire(starship_t *starship)
{
  if (starship->charge > FIRE_DRAIN) {
    entity_t *entity = (entity_t*)starship;
    int projectile_id = -1;
    if (entity->type == PLAYER)
      projectile_id = ((player_t*)starship)->player_id;
    uint16_t damage = 10 * (starship->weaponry + 1);
    projectile_t *projectile = malloc(sizeof(projectile_t));
    projectile_init(projectile, projectile_id, damage, {entity->movement.position, vec2_scale(entity->movement.orientation, PROJECTILE_VELOCITY), {0, 0}});
    stage_add_entity(stage, projectile);
    starship->charge -= FIRE_DRAIN;
  }
}

void starship_update(entity_t *entity, stage_t *stage)
{
  starship_t *starship = (starship_t*)entity;
  starship->charge++;
  entity_living_update((entity_t*)starship);
}
