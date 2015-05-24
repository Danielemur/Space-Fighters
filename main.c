#include <stdio.h>

#include "stage.h"
#include "asteroid.h"

#define STAGE_WIDTH 1500
#define STAGE_HEIGHT 1500
#define SPAWN_PERIOD 10
#define ASTEROID_COUNT 100
#define DEATH_CEILING 24

void stage_init(stage_t *stage)
{
*stage = (stage_t){0};
player_t *player = malloc(sizeof(player_t));
player_init(player, PLAYER_0, (movement_t){{0, 0}, {0, 0}, {0, 0}});
  stage_add_entity(stage, (entity_t*)player);
  uint32_t k = jenkins(stage->entity_count, STAGE_WIDTH, ASTEROID_COUNT);
  for (int i = 0; i < ASTEROID_COUNT; i++) {
    asteroid_t *asteroid = malloc(sizeof(asteroid_t));
    uint32_t rand = k = jenkins((i * k) >> (i << k), k >> ((k + i) << i), k + i);
    double x = STAGE_WIDTH * (1 - 2 * (rand & 0xffff) / (double) UINT16_MAX);
    double y = STAGE_HEIGHT * (1 - 2 * (rand >> 16) / (double) UINT16_MAX);
    rand = k = jenkins((i * k) >> (i << k), k >> ((k + i) << i), k + i);
    double x_rot = (1 - 2 * (rand & 0xffff) / (double) UINT16_MAX);
double y_rot = (1 - 2 * (rand >> 16) / (double) UINT16_MAX);
asteroid_init(asteroid, rand % 3, (movement_t){{x, y}, {0, 0}, {0, 0}, vec2_unitize((vec2_t){x_rot, y_rot})});
    stage_add_entity(stage, (entity_t*)asteroid);
  }
}

int main(int argc, char **argv)
{
  
  stage_t stage;
  stage_init(&stage);
  stage_run(&stage);
  stage_cleanup(&stage);
}
