#include <stdio.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#include "player.h"

#define PLAYER_SPEED 5;

void player_init(player_t* player,
		 player_id_t player_id,
		 movement_t movement)
{
  player->player_id = player_id;
  starship_init(&player->ship, PLAYER_HEALTH, PLAYER_ARMOR, PLAYER, movement);
}

void player_update(entity_t *entity,stage_t *stage)
{
  player_t *player = (player_t *)entity;
  int do_integer=play_char();
  
  double current_speed=vec2_mag(player->movement.velocity);
  
  if(current_speed <PLAYER_SPEED){
    if(ch=='w'){
      player->movement.acceleration={0,1};
    } else if(ch=='a'){
      player->movement.acceleration={-1,0};
    } else if(ch=='s'){
      player->movement.acceleration={0,-1};
    } else if(ch=='d'){
      player->movement.acceleration={1,0};
    }
  }else{
    player->movement.acceleration=vec2_scale(vec2_negate(player->movement.orientation),vec2_mag(player->movement.acceleration));
  }
  
  if(ch==' '){
    starship_fire(player);
  }
  
  
}

int play_char(){
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
