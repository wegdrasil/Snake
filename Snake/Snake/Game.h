#ifndef SGAMEH
#define SGAMEH

#include <SDL.h>
#include <glew.h>

class Game
{
	SDL_Window *window;

public:

	Game();
	~Game();
	void Initialize();
	void Run();

};

#endif

