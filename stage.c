#include <stdlib.h>
#include "stage.h"
#include "entity.h"
#include "player.h"
#include "enemy.h"
#include "asteroid.h"

void stage_add_entity(stage_t *stage, entity_t *entity)
{
    stage->entity_count++;
    entity->next = stage->entities;
    if (stage->entities != NULL)
        stage->entities->last = entity;
    stage->entities = entity;
}

void stage_remove_entity(stage_t *stage, entity_t *entity)
{
    stage->entity_count--;
    if (stage->status.is_running) {
        int x;
        if (entity->type == ENEMY) {
            enemy_t *enemy = (enemy_t*)entity;
            x = enemy->enemy_id;
            stage->status.death_count += (5/3) * (x * x * x) - 4 * (x * x) + (10/3) * x + 1;
            if (enemy->enemy_id == BOSS)
                stage->status.win = true;
        }
        else if (entity->type == PLAYER)
            stage->status.lose = true;
        }
    if (entity->last != NULL)
        entity->last->next = entity->next;
    else
        stage->entities = entity->next;
    if (entity->next != NULL)
        entity->next->last = entity->last;
    free(entity);
}

void stage_init(stage_t *stage)
{
    *stage = (stage_t){0};
    player_t *player = malloc(sizeof(player_t));
    player_init(player, PLAYER_0, (movement_t){{0, 0}, {0, 0}, {0, 0}, {0, 1}});
    stage_add_entity(stage, (entity_t*)player);
    for (int i = 0; i < ASTEROID_COUNT; i++) {
        asteroid_t *asteroid = malloc(sizeof(asteroid_t));
        int a = rand();
        int b = rand();
        double x = STAGE_WIDTH * (1 - 2 * (a / (double) RAND_MAX)) * 0.5;
        double y = STAGE_HEIGHT * (1 - 2 * (b / (double) RAND_MAX)) * 0.5;
        a = rand();
        b = rand();
        double x_rot = (1 - 2 * (a / (double) UINT16_MAX));
        double y_rot = (1 - 2 * (b / (double) UINT16_MAX));
        asteroid_init(asteroid, a % 3, (movement_t){{x, y}, {0, 0}, {0, 0}, vec2_unitize((vec2_t){x_rot, y_rot})});
        stage_add_entity(stage, (entity_t*)asteroid);
    }
}

void stage_cleanup(stage_t *stage)
{
    while (stage->entity_count > 0)
        stage_remove_entity(stage, stage->entities);
}

void stage_run(stage_t *stage, void (*stage_render)(stage_t *stage, void **context), void **context)
{
    stage->status.is_running = true;
    while(stage_step(stage))
    {
        stage_render(stage, context);
    }
    if (stage->status.win)
        printf("Congratulations! You win!\n");
    else if (stage->status.lose)
        printf("Too bad, you lose.\n");
}


int stage_step(stage_t *stage)
{
    stage->status.time += 1.0 / (double)FPS;
    int mode = (stage->status.death_count / DEATH_CEILING) + 1;
    int spawn_period = SPAWN_PERIOD * mode;
    if (stage->status.time > stage->status.spawn_duration && !stage->status.boss) {
        stage->status.next_spawn_time = stage->status.spawn_duration + SPAWN_PERIOD * jenkinsf(stage->entity_count, stage->status.next_spawn_time, stage->status.time);
        stage->status.spawn_duration += spawn_period;
        enemy_t *enemy = malloc(sizeof(enemy_t));
        int a = rand();
        int b = rand();
        double x = STAGE_WIDTH * (1 - 2 * (a / (double) RAND_MAX)) * 0.5;
        double y = STAGE_HEIGHT * (1 - 2 * (b / (double) RAND_MAX)) * 0.5;
        enemy_init(enemy, mode, (movement_t){{x, y}, {0, 0}, {0, 0}, {0, 1}});
        stage_add_entity(stage, (entity_t*)enemy);
        stage->status.boss = (mode == BOSS);
    }
    /*calculate velocity stuff as well as death of players and such*/
    for (unsigned i = PLAYER; i < ASTEROID; i++) {
        entity_t *entity = stage->entities;
        entity_t *entity_next;
        while (entity != NULL) {
            entity_next = entity->next;
            if (entity->type == i)
                entity->update(entity, stage);
            entity = entity_next;
        }
        
    }
    stage->status.is_running = !(stage->status.win || stage->status.lose);
    return (stage->status.is_running);
}
