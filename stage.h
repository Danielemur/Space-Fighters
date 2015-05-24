#pragma once

#include <stdlib.h>

typedef struct stage{
  size_t entity_count;
  entity_t *entity_list; //linked list
  bool boss_is_dead;
}stage_t;

void stage_add_entity(stage_t *stage, entity_t *entity);
