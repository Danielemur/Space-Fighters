#include <stdio.h>
#include "enemy.h"
#include "vec2.h"

#define ENEMY_ACCELERATION 1

void enemy_init(stage_t *stage,
		 enemy_t* enemy,
		 enemy_id_t enemy_id,
		 movement_t movement)
{
  enemy->enemy_id = enemy_id;
  starship_init(stage, &enemy->ship, PLAYER_HEALTH, PLAYER_ARMOR, ENEMY, movement);
}

void enemy_update(enemy_t *enemy)
{
  entity_t *entity = stage->entities;
  while(entity!=NULL){
    entity_type_t type = entities->type;
    if(type==PLAYER){
      vec2_t dir=vec2_unitize(vec2_sub(entity->movement->position,enemy->movement->position));
      
    }
    entity = entity->next;
  }    
}
