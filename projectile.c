#include "projectile.h"
#include "entity_living.h"
#include "asteroid.h"

void projectile_update(entity_t *entity, stage_t *stage)
{
  projectile_t *projectile = (projectile_t*)entity;
  entity_t *entity_test = stage->entities;
  while (stage->entities != NULL) {
    if (entity_test->type == PLAYER || entity_test->type == ENEMY) {
      starship_t *starship = (starship_t*)entity_test;
      if (vec2_dist(entity->movement.position, entity_test->movement.position) < PROJECTILE_HIT_RADIUS + starship->hit_radius) {
	starship->entity_live.health -= projectile->damage;
      }
    }
  }
  entity_test = stage->entities;
  while (stage->entities != NULL) {
    if (entity_test->type == ASTEROID) {
      entity_living_t *entity_live = (entity_living_t*)entity_test;
      if (vec2_dist(entity->movement.position, entity_test->movement.position) < PROJECTILE_HIT_RADIUS + ASTEROID_HIT_RADIUS) {
	entity_live->health = 0;
      }
    }
  }
  entity_living_update((entity_t*)projectile, stage);
}

void projectile_init(projectile_t *projectile,
		     int projectile_id,
		     uint16_t damage,
		     movement_t movement)
{
  projectile->projectile_id = projectile_id;
  projectile->damage = damage;
  projectile->entity_live.entity.update = projectile_update;
  entity_living_init(&projectile->entity_live, PROJECTILE_HEALTH, PROJECTILE, movement);
}
