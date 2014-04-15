#ifndef SGAMEH
#define SGAMEH

#include <SDL.h>
#include <glew.h>

#include "Renderer.h"

class Game
{
	SDL_Window *window;
	Renderer renderer;

	glm::vec2 mouse;

public:

	Game();
	~Game();

	void Initialize();
	void Run();

};

#endif

