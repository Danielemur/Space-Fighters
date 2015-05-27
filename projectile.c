#include "projectile.h"
#include "entity_living.h"
#include "asteroid.h"
#include "starship.h"
#include "player.h"
#include "stage.h"

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

void projectile_update(entity_t *entity, stage_t *stage)
{
    projectile_t *projectile = (projectile_t*)entity;
    for (entity_t *entity_test = stage->entities; entity_test != NULL; entity_test = entity_test->next) {
        if (entity_test->type == PLAYER || entity_test->type == ENEMY) {
            starship_t *starship = (starship_t*)entity_test;
            if (vec2_dist(entity->movement.position, entity_test->movement.position) < PROJECTILE_HIT_RADIUS + starship->hit_radius) {
                if ((entity_test->type == PLAYER && ((player_t*)starship)->player_id != (unsigned)projectile->projectile_id) ||
                    (entity_test->type == ENEMY && projectile->projectile_id != -1))
                    starship->entity_live.health -= projectile->damage;
            }
        }
    }
    for (entity_t *entity_test = stage->entities; entity_test != NULL; entity_test = entity_test->next) {
        if (entity_test->type == ASTEROID) {
            if (vec2_dist(entity->movement.position, entity_test->movement.position) < PROJECTILE_HIT_RADIUS + ASTEROID_HIT_RADIUS) {
                projectile->entity_live.health = 0;
            }
        }
    }
    vec2_t min = (vec2_t){-STAGE_WIDTH / 2, -STAGE_HEIGHT / 2};
    vec2_t max = (vec2_t){STAGE_WIDTH / 2, STAGE_HEIGHT / 2};
    if (!vec2_in_bounds(min, max, entity->movement.position))
        projectile->entity_live.health = 0;
    entity_living_update(entity, stage);
}
