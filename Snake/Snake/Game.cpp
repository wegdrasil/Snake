#include "Game.h"

Game::Game() {}
Game::~Game(){}

void Game::Initialize()
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	window = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	SDL_GL_CreateContext(window);

	glewInit();

	renderer.Initialize();

}

void Game::Run()
{
	const float lightskycolor[] = { 0.53f, 0.81f, 0.98f, 0.0f };
	bool quit = false;
	SDL_Event e;

	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			//User presses a key
			else if (e.type == SDL_KEYDOWN)
			{
				
			}
			else if (e.type == SDL_MOUSEMOTION)
			{
			}
		}

		renderer.Draw();

		SDL_GL_SwapWindow(window);
	}
	SDL_Quit();
}