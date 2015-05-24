#include <stdio.h>
#include <math.h>
#include "enemy.h"
#include "vec2.h"

#define ENEMY_ACCELERATION 1
#define ENEMY_SPEED 5;

void enemy_update(entity_t *entity,stage_t *stage)
{
  enemy_t *enemy = (enemy_t *)entity;
  entity_t *player_entity = stage->entities;
  double best_distance = INFINITY;
  entity_t *closest_entity;
  while (player_entity != NULL) {
    entity_type_t type = entities->type;
    if (type==PLAYER) {

      //checks speed >0 & <max enemy

      double distance = vec2_mag(vec2_sub(player_entity->movement.position, enemy->movement.position));
      if (distance < best_distance) {
	closest_entity = player_entity;
	best_distance = distance;
      }
    }
    player_entity = player_entity->next;
  }
  
  double current_speed = vec2_mag(enemy->movement.velocity);	
  if (best_distance < 70)
    starship_fire(enemy);
  enemy->movement.acceleration = vec2_scale(vec2_unitize(vec2_sub(closest_entity->movement.position, enemy->movement.position)), ENEMY_ACCELERATION);
 entity_update((entity*)enemy);
}

void enemy_init(stage_t *stage,
		 enemy_t* enemy,
		 enemy_id_t enemy_id,
		 movement_t movement)
{
  enemy->enemy_id = enemy_id;

  enemy->starship.entity_living.entity.update = enemy_update;
  starship_init(stage, &enemy->ship, PLAYER_HEALTH, PLAYER_ARMOR, ENEMY, ENEMY_HIT_RADIUS, movement);
}
