#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include "entity.h"

#define STAGE_WIDTH 1500
#define STAGE_HEIGHT 1500
#define SPAWN_PERIOD 10
#define ASTEROID_COUNT 2
#define DEATH_CEILING 24

typedef struct game_status {
    double time;
    double spawn_duration;
    double next_spawn_time;
    size_t death_count;
    bool is_running;
    bool boss;
    bool win;
    bool lose;
} game_status_t;

typedef struct stage {
    size_t entity_count;
    entity_t *entities; //linked list
    game_status_t status;
} stage_t;

void stage_add_entity(stage_t *stage, entity_t *entity);

void stage_remove_entity(stage_t *stage, entity_t *entity);

void stage_init(stage_t *stage);

void stage_cleanup(stage_t *stage);

void stage_run(stage_t *stage, void (*stage_render)(stage_t *stage, void **context), void **context);

int stage_step(stage_t *stage);
