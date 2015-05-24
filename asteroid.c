#include "asteroid.h"

void asteroit_init(asteroid_t *asteroid, int tex_id, movement_t movement)
{
  asteroid->tex_id = tex_id;
  entity_init(&asteroid->entity, ASTEROID, movement);
}

void asteroid_update(entity_t *entity, stage_t *stage)
{
  return;
}
