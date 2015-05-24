#include <stdio.h>
#include "starship.h"

void starship_init(stage_t *stage,
		   starship_t *starship,
		   uint16_t health,
		   uint16_t armor_level,
		   vec2_t position,
		   vec2_t velocity,
		   vec2_t acceleration);
{
  starship->armor_level = armor_level;
  starship->weaponry_level = weaponry_level;
  starship->charge = FULL_CHARGE;
  entity_living_init(stage, &starship->entity_live, health);
}
