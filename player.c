#include <stdio.h>
#include "player.h"

void player_init(stage_t *stage,
		 player_t* player,
		 player_id_t player_id,
		 vec2_t position,
		 vec2_t velocity,
		 vec2_t acceleration)
{
  player->player_id = player_id;
  starship_init(stage, &player->ship, PLAYER_HEALTH, PLAYER_ARMOR);
}
