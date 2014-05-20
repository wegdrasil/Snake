#include "Loser.h"


Loser::Loser()
{
}


Loser::~Loser()
{
}

void Loser::Initialize(SDL_Window *w, Renderer* r, Font* f)
{
	window = w;
	renderer = r;
	font = f;

	text[0].SetText(font, "Put your name on hall of fame and go back to menu", 250.0f, 450.0f);
	text[1].SetText(font, "next", 650.0f, 650.0f);

	textbox.Init(550.0f, 550.0f, font, "abc", 240);

	Sprite* ptr = &button.GetSprite();
	ptr->UpdateModelMatrixClip(glm::vec3(750.0f, 650.0f, 0.0f), 0.0f, glm::vec3(44.0f, 44, 0.0f));
	ptr->SetTexCoords(0, 461, 16, 16, 512.0f);
	ptr->SetColorInactive(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
	ptr->SetColorActive(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	ptr->SetColorHot(glm::vec4(0.9f, 0.9f, 0.9f, 1.0f));
	ptr->SetId(100);
	ptr->Initialize();

	choosen = 0;
}

void Loser::GuiUpdate()
{
	textbox.Logic(&gui.state, font);
	button.Logic(&gui.state);
}

void Loser::Draw()
{
	const float lightskycolor[] = { 0.305f, 0.305f, 0.305f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, lightskycolor);

	glUseProgram(renderer->shaderProgram);


	for (int j = 0; j < 2; j++)
	for (int i = 0; i < text[j].size; i++)
		renderer->DrawSprite(&text[j].GetSprite()[i]);

	renderer->DrawSprite(&textbox.GetButtonSprite());

	for (int i = 0; i < textbox.GetText().size; i++)
	{
		renderer->DrawSprite(&textbox.GetText().GetSprite()[i]);
	}


	renderer->DrawSprite(&button.GetSprite());
	glFlush();
}

void Loser::DrawSelection()
{
	const float blackcolor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, blackcolor);

	glUseProgram(renderer->selectionProgram);

	renderer->DrawSpriteSelection(&textbox.GetButtonSprite());

	renderer->DrawSpriteSelection(&button.GetSprite());
	glFlush();
}

unsigned char Loser::ProcessSelection(int x, int y)
{
	unsigned char response[4];
	GLint viewport[4];

	DrawSelection();
	DrawSelection();

	glGetIntegerv(GL_VIEWPORT, viewport);
	glReadPixels(x, viewport[3] - y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &response);

	return response[0];
}
Score Loser::Run(int points)
{
	bool quit = false;
	SDL_Event e;
	inputText = "";

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{

			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0)
				{
					if (gui.state.activeTextbox)
					{
						inputText.pop_back();
						gui.ReceiveText(inputText);
					}
				}
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

			GuiUpdate();
			Draw();
			switch (choosen)
			{
			case 100:
				quit = true;
				choosen = 0;
				score.name = inputText;
				score.points = points;
				printf("100\n");
				return  score;
			default:
				;
			}

			SDL_GL_SwapWindow(window);

		}
	}
	score.name = "noname";
	score.points = -2;
	return  score;
}