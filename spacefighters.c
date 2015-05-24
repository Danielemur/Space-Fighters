#include <stdio.h>
#include "entity_living.h"
#include "player.h"
#include "stage.h"
#include "starship.h"
#include "boss.h"
#include "entity.h"

void stage_init(stage_t *stage){
  /*setup pos and stuff here*/
  player_t player;
  player_init(stage, &player, 0);
  
  /*game done*/
}

void stage_run(){
  /*setup pos and stuff here*/
  
  while(stage_step())
    {
      
    }
  /*game cleanup*/
}


int stage_step(){
  /*calculate velocity stuff as well as death of players and such*/

  return 1;
}
