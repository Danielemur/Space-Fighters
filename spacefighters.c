#pragma once

#include <stdio.h>


void stage_Initialize(){
	/*setup pos and stuff here*/
	int done=0;
	while(done!=1){
		done=step();
	}
	/*game done*/
}


int stage_Step(){
	/*calculate velocity stuff as well as death of players and such*/

	return 1;
}
