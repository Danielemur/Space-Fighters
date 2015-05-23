#pragma once

#include "starship.h"

#define PLAYER_HEALTH 100
#define PLAYER_ARMOR 0

typedef enum
  {
    PLAYER_0, PLAYER_1, PLAYER_2, PLAYER_3
  } player_id_t;

typedef struct player{
  starship_t ship;
  player_id_t player_id;
} player_t;

void player_init(stage_t *stage,
		 player_t* player,
		 player_id_t player_id,
		 vec2_t position,
		 vec2_t velocity,
		 vec2_t acceleration);
