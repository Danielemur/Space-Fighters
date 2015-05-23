#pragma once

#include <stdlib.h>

typedef struct stage{
  size_t entity_count;
  entity_t *entity_list; //linked list
}stage_t;
