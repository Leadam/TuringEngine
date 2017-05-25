#include "graphics.h"
#include <SDL2/SDL.h>
#include <iostream>
void init_te_graphics(){
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
		std::cerr <<"SDL Initialization faild"<<std::endl;
	}
}

void quit_te_graphics(){
	SDL_Quit();
}

