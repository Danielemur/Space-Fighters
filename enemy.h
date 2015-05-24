#pragma once

#include "starship.h"
#include "stage.h"

#define ENEMY_ACCELERATION 1
#define ENEMY_SPEED 5;
#define ENEMY_0_HEALTH 30
#define ENEMY_0_ARMOR 1
#define ENEMY_1_HEALTH 50
#define ENEMY_1_ARMOR 1
#define ENEMY_2_HEALTH 100
#define ENEMY_2_ARMOR 2
#define BOSS_HEALTH 500
#define BOSS_ARMOR 4
#define ENEMY_TYPE_COUNT 4
#define ENEMY_HIT_RADIUS 25

typedef enum
  {
    ENEMY_0, ENEMY_1, ENEMY_2, BOSS
  } enemy_id_t;

typedef struct enemy{
  starship_t ship;
  enemy_id_t enemy_id;
} enemy_t;

void enemy_init(stage_t *stage,
		enemy_t *enemy,
		enemy_id_t enemy_id,
	        movement_t movement);
