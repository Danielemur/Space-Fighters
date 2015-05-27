#include <stdio.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#include "player.h"
#include "starship.h"
#include "stage.h"

static int 
play_char(){
  //got to check if window focus
  struct termios oldt, newt;
  int ch;
  
  tcgetattr( STDIN_FILENO, &oldt);
  newt=oldt;
  newt.c_lflag &= ~(ICANON);
  tcsetattr( STDIN_FILENO, TCSANOW, &newt);
  ch=getchar();
  tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
  
  //check stuff, return vals
  return ch;
}  

void player_init(player_t* player,
		 player_id_t player_id,
		 movement_t movement)
{
  player->player_id = player_id;
  player->ship.entity_live.entity.update=player_update;
  starship_init(&player->ship, PLAYER_HEALTH, PLAYER_ARMOR, PLAYER_WEAPONRY, PLAYER_HIT_RADIUS, PLAYER, movement);
}   

void player_update(entity_t *entity, stage_t *stage)
{
  player_t *player = (player_t *)entity;
  /* int do_integer = play_char(); */
  
  /* double current_speed = vec2_mag(entity->movement.velocity); */
  
  /* if (current_speed < PLAYER_SPEED) { */
  /*   if (do_integer == 'w') { */
  /*     entity->movement.acceleration = (vec2_t){0, 1}; */
  /*   } else if (do_integer == 'a') { */
  /*     entity->movement.acceleration = (vec2_t){-1, 0}; */
  /*   } else if (do_integer == 's') { */
  /*     entity->movement.acceleration = (vec2_t){0, -1}; */
  /*   } else if (do_integer == 'd') { */
  /*     entity->movement.acceleration = (vec2_t){1, 0}; */
  /*   } */
  /* }else{ */
  /*   entity->movement.acceleration=vec2_scale(entity->movement.orientation, -PLAYER_ACCELERATION); */
  /* } */
  
  /* if(do_integer == ' '){ */
  /*   starship_fire((starship_t*)player, stage); */
  /* } */
  bool still_alive = starship_update(entity, stage);
  if (still_alive) {
      entity->movement.velocity = vec2_min(entity->movement.velocity, (vec2_t){PLAYER_SPEED, PLAYER_SPEED});
      entity->movement.position = vec2_min(vec2_max(entity->movement.position, (vec2_t){-STAGE_WIDTH / 2, -STAGE_HEIGHT / 2}), (vec2_t){STAGE_WIDTH / 2, STAGE_HEIGHT / 2});
  }
}
