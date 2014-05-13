#ifndef SAPPH
#define SAPPH

#include <SDL.h>
#include <glew.h>

#include "Renderer.h"
//#include "GUI.h"

#include "Font.h"
//#include "Text.h"

#include "StartGame.h"

#include <iostream>

class App
{
	SDL_Window *window;
	Renderer renderer;
	//GUI gui;
	Font font;
	
	StartGame startGame;
	//std::string inputText;

public:
	App();
	~App();

	void Initialize();
	void Run();
};

#endif

