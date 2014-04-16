#include "Application.h"

App::App() {}
App::~App(){}

void App::Initialize()
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	window = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );

	SDL_GL_CreateContext(window);

	glewInit();

	renderer.Initialize();

}

void App::Run()
{
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
				float offset = 0.0007f;
				switch (e.key.keysym.sym)
				{
				case SDLK_p:
					std::cout << gui.mouseX << " " << gui.mouseY << "\n";
					break;
				case SDLK_w:
					break;
				case SDLK_s:
					break;
				case SDLK_a:
					break;
				case SDLK_d:
					break;
				}
			}
			else if (e.type == SDL_MOUSEMOTION)
			{
				gui.mouseX = e.motion.x;
				gui.mouseY = e.motion.y;
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (e.button.button == true)
					gui.mousedown = true;

				renderer.ProcessSelection(gui.mouseX, gui.mouseY);
			}
			else if (e.type == SDL_MOUSEBUTTONUP)
			{
				if (e.button.button == true)
					gui.mousedown = false;
			}
			else if (e.type == SDL_WINDOWEVENT)
			{
				switch (e.window.event)
				{
					case SDL_WINDOWEVENT_RESIZED:
						renderer.Resize(e.window.data1, e.window.data2);
						break;
				}
			}
		}

		renderer.Update();
		renderer.Draw();

		SDL_GL_SwapWindow(window);
	}

	SDL_Quit();
}