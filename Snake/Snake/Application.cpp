#include "Application.h"
#include <stdio.h>
#include <string.h>

App::App() {}
App::~App(){}

void App::Initialize()
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	window = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
	
	SDL_GL_CreateContext(window);
	glewExperimental = GL_TRUE;
	
	glewInit();
	
	font.ParseFontFile("font.fnt");		
	renderer.Initialize();

	startGame.Initialize(window, &renderer, &font);
	startGame.Run();

	SDL_Quit();
}