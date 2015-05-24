#include "asteroid.h"

void asteroid_update(entity_t *entity, stage_t *stage)
{
  return;
}

void asteroit_init(asteroid_t *asteroid, int tex_id, movement_t movement)
{
  asteroid->tex_id = tex_id;
  asteroid->entity.update = asteroid_update;
  entity_init(&asteroid->entity, ASTEROID, movement);
}
