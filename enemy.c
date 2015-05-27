#include <stdio.h>
#include <math.h>
#include "enemy.h"
#include "starship.h"
#include "stage.h"

void enemy_init(enemy_t* enemy,
                enemy_id_t enemy_id,
                movement_t movement)
{
    enemy->enemy_id = enemy_id;
  
    enemy->ship.entity_live.entity.update = enemy_update;
    uint16_t health;
    uint16_t armor;
    uint16_t weaponry;
    if (enemy_id == ENEMY_0) {
        health = ENEMY_0_HEALTH;
        armor = ENEMY_0_ARMOR;
        weaponry = ENEMY_0;
    }
  
    if (enemy_id == ENEMY_1) {
        health = ENEMY_1_HEALTH;
        armor = ENEMY_1_ARMOR;
        weaponry = ENEMY_1;
    }
  
    if (enemy_id == ENEMY_2) {
        health = ENEMY_2_HEALTH;
        armor = ENEMY_2_ARMOR;
        weaponry = ENEMY_2;
    }
    
    if (enemy_id == BOSS) {
        health = BOSS_HEALTH;
        armor = BOSS_ARMOR;
        weaponry = BOSS;
    } 
    starship_init(&enemy->ship, health, armor, weaponry, ENEMY_HIT_RADIUS, ENEMY, movement);
}

void enemy_update(entity_t *entity, stage_t *stage)
{
    enemy_t *enemy = (enemy_t *)entity;
    entity_t *player_entity = stage->entities;
    double best_distance = INFINITY;
    entity_t *closest_entity = stage->entities;
    while (player_entity != NULL) {
        if (player_entity->type == PLAYER) {
            //checks speed >0 & <max enemy
            double distance = vec2_mag(vec2_sub(player_entity->movement.position, entity->movement.position));
            if (distance < best_distance) {
                closest_entity = player_entity;
                best_distance = distance;
            }
        }
        player_entity = player_entity->next;
    }
  	
    if (best_distance < 70)
        starship_fire((starship_t*)enemy, stage);
    entity->movement.acceleration = vec2_scale(vec2_unitize(vec2_sub(closest_entity->movement.position, entity->movement.position)), ENEMY_ACCELERATION);
    bool still_alive = starship_update(entity, stage);
    if (still_alive) {
        entity->movement.velocity = vec2_min(entity->movement.velocity, (vec2_t){ENEMY_SPEED, ENEMY_SPEED});
        entity->movement.position = vec2_min(vec2_max(entity->movement.position, (vec2_t){-STAGE_WIDTH / 2, -STAGE_HEIGHT / 2}), (vec2_t){STAGE_WIDTH / 2, STAGE_HEIGHT / 2});
    }
}
