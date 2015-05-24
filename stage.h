#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include "entity.h"
#include "player.h"

typedef struct stage{
  size_t entity_count;
  entity_t *entities; //linked list
  size_t death_count;
  double time;
  double spawn_duration;
  double next_spawn_time;
  bool boss;
  bool boss_is_dead;
}stage_t;

void stage_add_entity(stage_t *stage, entity_t *entity);

void stage_remove_entity(stage_t *stage, entity_t *entity);

void stage_init(stage_t *stage);

void stage_cleanup(stage_t *stage);

void stage_run(stage_t *stage);

int stage_step(stage_t *stage);
