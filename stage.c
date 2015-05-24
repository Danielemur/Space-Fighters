#include "stage.h"
#include "common.h"

#define STAGE_WIDTH 1500
#define STAGE_HEIGHT 1500
#define FPS 15
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

void stage_init(stage_t *stage)
{
  /*setup pos and stuff here*/
  *stage= {0};
  player_t *player = malloc(sizeof(player_t));
  player_init(stage, player, PLAYER_0, DEFAULT_MOVEMENT);
  stage_add_entity(stage, (entity*)player);
  uint32_t k = jenkins(stage->entity_count, STAGE_WIDTH, ASTEROID_COUNT);
  for (int i = 0; i < asteroid_count; i++) {
    asteroid_t *asteroid = malloc(sizeof(asteroid_t));
    uint32_t rand = k = jenkins((i * k) % (i << k), k % ((k / i) << i), k + i);
    double x = STAGE_WIDTH * (1 - 2 * (rand & 0xffff) / (vfloat) UINT16_MAX);
    double y = STAGE_HEIGHT * (1 - 2 * (rand >> 16) / (vfloat) UINT16_MAX);
    asteroid_init(stage, asteroid, rand % 3, {{x, y}, {0, 0}, {0, 0}});
    stage_add_entity(stage, (entity*)asteroid);
  }
}

void stage_run(stage_t *stage)
{
  while(stage_step(stage))
    {
      /* image generation and display */
    }
  /*game cleanup*/
  while (stage->entity_count > 0)
    stage_remove_entity(stage, stage->entities);
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
    enemy_init(stage, enemy, mode, DEFAULT_MOVEMENT);
    stage_add_entity(stage, (entity*)enemy);
    stage->boss = (mode == BOSS);
  }
  /*calculate velocity stuff as well as death of players and such*/
  entity_t *entity = stage->entities;
  for (int i = 0; i < ENTITY_TYPE_NUMBER; i++) {
    while (entity != NULL) {
      if (entity->type == i)
	entity_update(entity);
      entity = entity->next;
    }
    entity = stage->entities;
  }
  return !stage->boss_is_dead;
}
