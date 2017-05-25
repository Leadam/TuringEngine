#ifndef CHART_H
#define CHART_H
#include <SDL2/SDL.h>
#include <vector>

class chart{
private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	
	std::vector<double>* _data;
	
	void _drawGrid();
public:
	chart();
	void setDataSet(std::vector<double>& data);
	void update();
	~chart();
};

#endif // CHART_H
