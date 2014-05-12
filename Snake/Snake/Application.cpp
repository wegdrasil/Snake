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
	
	font.ParseFontFile("test.fnt");		
	gui.Initialize(&font);
	inputText = "";
	renderer.Initialize(&gui);
}

void App::Run()
{
	bool quit = false;
	SDL_Event e;

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				float offset = 0.0007f;
				switch (e.key.keysym.sym)
				{
				case SDLK_p:
					std::cout << gui.state.mouseX << " " << gui.state.mouseY << "\n";
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
				if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0)
				{
					if (gui.state.activeTextbox )
					{
						inputText.pop_back();
						gui.ReceiveText(inputText);
					}
				}
				/*if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
				{
					if (gui.state.activeTextbox)
					{
						inputText += SDL_GetClipboardText();
						if( inputText.size() < 15)
							gui.ReceiveText(inputText);
					}
				}*/
			}
			else if (e.type == SDL_TEXTINPUT)
			{
				if (!((e.text.text[0] == 'c' || e.text.text[0] == 'C') && (e.text.text[0] == 'v' || e.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL))
				{
					if (gui.state.activeTextbox && inputText.size() < 15)
					{
						inputText += e.text.text;
						gui.ReceiveText(inputText);
					}
				}
			}
			else if (e.type == SDL_MOUSEMOTION)
			{
				gui.state.mouseXLast = gui.state.mouseX;
				gui.state.mouseYLast = gui.state.mouseY;

				gui.state.mouseX = e.motion.x;
				gui.state.mouseY = e.motion.y;
				
				unsigned char id = renderer.ProcessSelection(gui.state.mouseX, gui.state.mouseY);

				if (id == 0)
				{
					gui.state.idHot = 0;
					gui.state.hot = false;
				}
				else
				{	
					if (gui.state.idHot != id)
						gui.state.hot = false;

					gui.state.idHot = id;
					gui.state.hot = true;
				}
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (e.button.button == true)
					gui.state.mousedown = true;
				
				if (e.button.state == SDL_PRESSED)
					gui.state.mousepressed = true;

				unsigned char id = renderer.ProcessSelection(gui.state.mouseX, gui.state.mouseY);
				
				if ( id == 0)
				{
					gui.state.active = false;
					gui.state.idIsZero = true;
				}
				else
				{
					gui.state.idActive = id;
					gui.state.active = true;
					gui.state.idIsZero = false;
				}
			
			}
			else if (e.type == SDL_MOUSEBUTTONUP)
			{
				gui.state.mousepressed = false;
				if (e.button.button == true)
					gui.state.mousedown = false;

				gui.state.idActive = 0;
				gui.state.active = false;
				gui.state.idIsZero = false;



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
		
		gui.Update();
		renderer.Update();
		renderer.Draw();

		SDL_GL_SwapWindow(window);
	}

	SDL_Quit();
}