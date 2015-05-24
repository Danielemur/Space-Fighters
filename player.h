#pragma once

#include "starship.h"

#define PLAYER_HEALTH 100
#define PLAYER_ARMOR 0
#define PLAYER_TYPE_COUNT 4

typedef enum
  {
    PLAYER_0, PLAYER_1, PLAYER_2, PLAYER_3
  } player_id_t;

typedef struct player{
  starship_t ship;
  player_id_t player_id;
} player_t;

void player_init(player_t* player,
		 player_id_t player_id,
		 movement_t movement);
