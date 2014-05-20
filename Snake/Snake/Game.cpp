#include "Game.h"


Game::Game()
{
}


Game::~Game()
{
}

void Game::Initialize(SDL_Window *w, Renderer* r, Font* f)
{
	window = w;
	renderer = r;
	font = f;

	text[0].SetText(font, "Points", 700.0f, 1100.0f);
	text[1].SetText(font, "0", 900.0f, 1100.0f);

	choosen = 0;
	lastInput = 'd';

	board.Initialize(renderer);
	mouse.GetNewPosition();
	mouse.Initialize(renderer);
	loser.Initialize(window, renderer, font);

	logic.Initialize();
}

void Game::Reset()
{
	board.Initialize(renderer);
	mouse.GetNewPosition();
	mouse.Initialize(renderer);
	loser.Initialize(window, renderer, font);

	logic.Initialize();
}

void Game::GuiUpdate()
{
}

void Game::Draw()
{
	const float lightskycolor[] = { 0.305f, 0.305f, 0.305f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, lightskycolor);

	glUseProgram(renderer->shaderProgram);

	board.Draw();
	mouse.Draw();
	snake.Draw();

	for (int j = 0; j < 2; j++)
	for (int i = 0; i < text[j].size; i++)
		renderer->DrawSprite(&text[j].GetSprite()[i]);

	glFlush();
}

void Game::DrawSelection()
{
	const float blackcolor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, blackcolor);

	glUseProgram(renderer->selectionProgram);


	glFlush();
}

unsigned char Game::ProcessSelection(int x, int y)
{
	unsigned char response[4];
	GLint viewport[4];

	DrawSelection();
	DrawSelection();

	glGetIntegerv(GL_VIEWPORT, viewport);
	glReadPixels(x, viewport[3] - y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &response);

	return response[0];
}
Score Game::Run(int difflevel)
{
	bool quit = false;
	SDL_Event e;

	snake.SetDificultyLevel(difflevel);
	snake.Initialize(renderer);

	for (int i = 0; i < snake.GetSize(); i++)
		snake.Update('d');

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{

			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_UP:
					snake.Update('w');
					lastInput = 'w';
					break;
				case SDLK_DOWN:
					snake.Update('s');
					lastInput = 's';
					break;
				case SDLK_LEFT:
					snake.Update('a');
					lastInput = 'a';
					break;
				case SDLK_RIGHT:
					snake.Update('d');
					lastInput = 'd';
					break;
				}
			}
			else if (e.type == SDL_MOUSEMOTION)
			{
				gui.state.mouseXLast = gui.state.mouseX;
				gui.state.mouseYLast = gui.state.mouseY;

				gui.state.mouseX = e.motion.x;
				gui.state.mouseY = e.motion.y;

				unsigned char id = ProcessSelection(gui.state.mouseX, gui.state.mouseY);

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

				unsigned char id = ProcessSelection(gui.state.mouseX, gui.state.mouseY);

				choosen = id;

				if (id == 0)
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
					renderer->Resize(e.window.data1, e.window.data2);
					break;
				}
			}
		}

		GuiUpdate();

		snake.Update(lastInput);
		text[1].SetText(font, std::to_string(logic.GetPoints()), 900.0f, 1100.0f);

		if (!logic.Run(&snake, &mouse, &board))
		{
			score = loser.Run(logic.GetPoints());
			quit = true;

			return score;
		}


		Draw();

		SDL_GL_SwapWindow(window);
		SDL_Delay(200);
	}
	score.name = "noname";
	score.points = -1;
	return score;
}