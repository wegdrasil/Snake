#ifndef SOPTIONSH
#define SOPTIONSH

#include "Renderer.h"
#include "GUI.h"
#include "Text.h"
#include "Checkbox.h"
#include "Button.h"
#include "Font.h"

class Options
{
	SDL_Window *window;
	Renderer* renderer;
	GUI gui;
	Font* font;

	Checkbox checkbox[4];
	Text text[3];

	Button button;

	unsigned int choosen;

public:
	Options();
	~Options();

	void Initialize(SDL_Window *w, Renderer* r, Font* f)
	{
		window = w;
		renderer = r;
		font = f;

		text[0].SetText(font, "Options", 730.0f, 350.0f);
		text[1].SetText(font, "Choose level of difficulty", 550.0f, 400.0f);
		text[2].SetText(font, "return to the menu", 650.0f, 700.0f);

		checkbox[0].Init(600.0f, 450.0f, font, "very easy (default)", 200);
		checkbox[1].Init(600.0f, 500.0f, font, "easy ", 201);
		checkbox[2].Init(600.0f, 550.0f, font, "medium", 202);
		checkbox[3].Init(600.0f, 600.0f, font, "hard", 203);

		Sprite* ptr = &button.GetSprite();
		ptr->UpdateModelMatrixClip(glm::vec3(600.0f, 700.0f, 0.0f), 0.0f, glm::vec3(44.0f, 44, 0.0f));
		ptr->SetTexCoords(0, 424, 13, 13, 512.0f);
		ptr->SetColorInactive(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
		ptr->SetColorActive(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		ptr->SetColorHot(glm::vec4(0.9f, 0.9f, 0.9f, 1.0f));
		ptr->SetId(100);
		ptr->Initialize();

		choosen = 0;
	}

	void GuiUpdate()
	{
		for (int i = 0; i < 4; i++)
			checkbox[i].Logic(&gui.state);

		button.Logic(&gui.state);
	}

	void Draw()
	{
		const float lightskycolor[] = { 0.305f, 0.305f, 0.305f, 0.0f };
		glClearBufferfv(GL_COLOR, 0, lightskycolor);

		glUseProgram(renderer->shaderProgram);

		renderer->DrawSprite(&button.GetSprite());

		for (int i = 0; i < 4; i++)
			renderer->DrawSprite(&checkbox[i].GetButtonSprite());
		
		for (int j = 0; j < 4; j++)
		{
			Text* ptr = &checkbox[j].GetText();
			for (int i = 0; i < ptr->size; i++)
			{
				renderer->DrawSprite(&ptr->GetSprite()[i]);
			}
		}

		for (int j = 0; j < 3; j++)
			for (int i = 0; i < text[j].size; i++)
				renderer->DrawSprite(&text[j].GetSprite()[i]);

		glFlush();
	}

	void DrawSelection()
	{
		const float blackcolor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		glClearBufferfv(GL_COLOR, 0, blackcolor);

		glUseProgram(renderer->selectionProgram);
		
		renderer->DrawSpriteSelection(&button.GetSprite());

		for (int i = 0; i < 4; i++)
			renderer->DrawSpriteSelection(&checkbox[i].GetButtonSprite());
		
		glFlush();
	}

	unsigned char ProcessSelection(int x, int y)
	{
		unsigned char response[4];
		GLint viewport[4];

		DrawSelection();
		DrawSelection();

		glGetIntegerv(GL_VIEWPORT, viewport);
		glReadPixels(x, viewport[3] - y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &response);

		return response[0];
	}
	int Run()
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

				switch (choosen)
				{
				case 100:
					printf("Quit\n");
					quit = true;
					choosen = 0;
					break;
				default:
					printf("Res: %d\n", choosen);
				}

				Draw();

				SDL_GL_SwapWindow(window);
			}
		}

		for (int i = 0; i < 4; i++)
			if (checkbox[i].on)
				return i;
	}
};
#endif

