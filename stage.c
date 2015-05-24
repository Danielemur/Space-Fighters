#include "stage.h"
#include "entity.h"
#include "player.h"
#include "enemy.h"

#define STAGE_WIDTH 1500
#define STAGE_HEIGHT 1500
#define SPAWN_PERIOD 10
#define ASTEROID_COUNT 100
#define DEATH_CEILING 24

void stage_add_entity(stage_t *stage, entity_t *entity)
{
  stage->entity_count++;
  entity->next = stage->entities;
  stage->entities = entity;
}

void stage_remove_entity(stage_t *stage, entity_t *entity)
{
  stage->entity_count--;
  if (entity->last != NULL)
    entity->last->next = entity->next;
  if (entity->next != NULL)
    entity->next->last = entity->last;
  free(entity);
}

void stage_cleanup(stage_t *stage)
{
  while (stage->entity_count > 0)
    stage_remove_entity(stage, stage->entities);
  free(stage);
}

void stage_run(stage_t *stage)
{
  while(stage_step(stage))
    {
      /* image generation and display */
    }
  /*game end*/
}


int stage_step(stage_t *stage)
{
  stage->time += 1.0 / FPS;
  int mode = stage->death_count / DEATH_CEILING;
  int spawn_period = SPAWN_PERIOD * mode;
  if (stage->time > stage->spawn_duration && !stage->boss) {
    stage->next_spawn_time = stage->spawn_duration + SPAWN_PERIOD * jenkinsf(stage->entity_count, stage->next_spawn_time, stage->time);
    stage->spawn_duration += spawn_period;
    enemy_t *enemy;
    enemy_init(stage, enemy, mode, (movement_t){{0, 0}, {0, 0}, {0, 0}});
    stage_add_entity(stage, (entity_t*)enemy);
    stage->boss = (mode == BOSS);
  }
  /*calculate velocity stuff as well as death of players and such*/
  entity_t *entity = stage->entities;
  for (int i = 0; i < ENTITY_TYPE_NUMBER; i++) {
    while (entity != NULL) {
      if (entity->type == i)
	entity_update(entity, stage);
      entity = entity->next;
    }
    entity = stage->entities;
  }
  return !stage->boss_is_dead;
}
