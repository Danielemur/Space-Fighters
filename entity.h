#pragma once

typedef struct entity{
  vec2_t position;
  vec2_t velocity;
  vec2_t acceleration;
} entity_t;

void entity_create();

void set_position(entity_t *entity);

void set_velocity(entity_t *entity);

void set_acceleration(entity_t *entity);
