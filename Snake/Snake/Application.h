#ifndef SAPPH
#define SAPPH

#include <SDL.h>
#include <glew.h>

#include "Renderer.h"
#include "Font.h"
#include "StartGame.h"

#include <iostream>

class App
{
	SDL_Window *window;
	Renderer renderer;
	Font font;
	
	StartGame startGame;

public:
	App();
	~App();

	void Initialize();
	void Run();
};

#endif

