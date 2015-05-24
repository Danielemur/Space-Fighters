#include <stdio.h>
#include "enemy.h"

void enemy_init(stage_t *stage,
		 enemy_t* enemy,
		 enemy_id_t enemy_id,
		 movement_t movement)
{
  enemy->enemy_id = enemy_id;
  starship_init(stage, &enemy->ship, PLAYER_HEALTH, PLAYER_ARMOR, movement);
}
