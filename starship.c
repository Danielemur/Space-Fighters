#include <stdio.h>
#include "starship.h"

void starship_init(starship_t *starship,
		   uint16_t health,
		   uint16_t armor_level,
		   entity_type_t type,
		   movement_t movement);
{
  starship->armor_level = armor_level;
  starship->weaponry_level = weaponry_level;
  starship->charge = FULL_CHARGE;
  entity_living_init(&starship->entity_live, health, type, movement);
}
