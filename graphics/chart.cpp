#include "chart.h"
#include <algorithm>
#include <iostream>
chart::chart(){
	_window = SDL_CreateWindow("Chart",
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				640, 480,
				0);
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
}

void chart::setDataSet(std::vector< double >& data){
	_data = &data;
}

void chart::_drawGrid(){
	double max = *std::max_element(_data->begin(),_data->end());
	double min = std::min(*std::min_element(_data->begin(),_data->end()), 0.0);
	
	double stepx = 640.0 / _data->size();
	double stepy = 480.0 / (max - min);
	
	while(stepy < 10.0) stepy *= 10.0;
	while(stepy > 100.0) stepy /= 100.0;
	
	
	while(stepx < 10.0) stepx *= 10.0;
	
	
	SDL_SetRenderDrawColor(_renderer,120,120,120,255);
	
	for(double x=0; x < 640.0; x+=stepx){
		SDL_RenderDrawLine(_renderer,x,0,x,480);
	}

	for(double y=0; y < 480.0; y+=stepy){
		SDL_RenderDrawLine(_renderer,0,y,640,y);
	}
	
	stepx = 640.0 / _data->size();
	stepy = 480.0 / (max - min);
	SDL_SetRenderDrawColor(_renderer,255,0,0,255);

	for(int i=1; i<_data->size(); ++i){
		SDL_RenderDrawLine(_renderer,(i-1)*stepx,480.0 - (_data->at(i-1)*stepy),i*stepx,480.0 - (_data->at(i)*stepy));		
	}
}



void chart::update(){
	if(!_window) return;
	if(SDL_QuitRequested()){
		SDL_DestroyRenderer(_renderer);
		_renderer = 0;
		SDL_DestroyWindow( _window );
		_window = 0;
		return;
	}
	SDL_SetRenderDrawColor(_renderer,100,100,100,255);
	SDL_RenderClear(_renderer);
	_drawGrid();
	
	SDL_RenderPresent(_renderer);
}

chart::~chart(){
	
	
}
