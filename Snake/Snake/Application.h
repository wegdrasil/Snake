#ifndef SAPPH
#define SAPPH

#include <SDL.h>
#include <glew.h>

#include "Renderer.h"
#include "GUI.h"

class App
{
	SDL_Window *window;
	Renderer renderer;
	GUI gui;
	
public:
	App();
	~App();

	void Initialize();
	void Run();
};

#endif

