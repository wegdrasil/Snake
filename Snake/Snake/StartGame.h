#ifndef SSTARTGAMEH
#define SSTARTGAMEH

#include "Renderer.h"
#include "GUI.h"
#include "Text.h"
#include "Font.h"

class StartGame
{
	SDL_Window *window;
	Renderer* renderer;
	GUI gui;
	Font* font;

	Text text[5];
	Button button[4];

	unsigned int choosen;

public:
	StartGame();
	~StartGame();

	void Initialize(SDL_Window *w, Renderer* r, Font* f)
	{
		window = w;
		renderer = r;
		font = f;

		text[0].SetText(font, "SNAKE", 700.0f, 350.0f);
		text[1].SetText(font, "New Game", 700.0f, 400.0f);
		text[2].SetText(font, "Hall of Fame", 700.0f, 450.0f);
		text[3].SetText(font, "Options", 700.0f, 500.0f);
		text[4].SetText(font, "Quit", 700.0f, 550.0f);

		Sprite* ptr = &button[0].GetSprite();
		ptr->UpdateModelMatrixClip(glm::vec3(650.0f, 400.0f, 0.0f), 0.0f, glm::vec3(44.0f, 44, 0.0f));
		ptr->SetTexCoords(0, 424, 13, 13, 512.0f);
		ptr->SetColorInactive(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
		ptr->SetColorActive(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		ptr->SetColorHot(glm::vec4(0.9f, 0.9f, 0.9f, 1.0f));
		ptr->SetId(100);
		ptr->Initialize();

		ptr = &button[1].GetSprite();
		ptr->UpdateModelMatrixClip(glm::vec3(650.0f, 450.0f, 0.0f), 0.0f, glm::vec3(44.0f, 44, 0.0f));
		ptr->SetTexCoords(0, 424, 13, 13, 512.0f);
		ptr->SetColorInactive(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
		ptr->SetColorActive(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		ptr->SetColorHot(glm::vec4(0.9f, 0.9f, 0.9f, 1.0f));
		ptr->SetId(101);
		ptr->Initialize();

		ptr = &button[2].GetSprite();
		ptr->UpdateModelMatrixClip(glm::vec3(650.0f, 500.0f, 0.0f), 0.0f, glm::vec3(44.0f, 44, 0.0f));
		ptr->SetTexCoords(0, 424, 13, 13, 512.0f);
		ptr->SetColorInactive(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
		ptr->SetColorActive(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		ptr->SetColorHot(glm::vec4(0.9f, 0.9f, 0.9f, 1.0f));
		ptr->SetId(102);
		ptr->Initialize();

		ptr = &button[3].GetSprite();
		ptr->UpdateModelMatrixClip(glm::vec3(650.0f, 550.0f, 0.0f), 0.0f, glm::vec3(44.0f, 44, 0.0f));
		ptr->SetTexCoords(0, 424, 13, 13, 512.0f);
		ptr->SetColorInactive(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
		ptr->SetColorActive(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		ptr->SetColorHot(glm::vec4(0.9f, 0.9f, 0.9f, 1.0f));
		ptr->SetId(103);
		ptr->Initialize();

		choosen = 0;
	}

	void GuiUpdate()
	{
		for (int i = 0; i < 4; i++)
			button[i].Logic(&gui.state);

		switch (choosen)
		{
		case 0: printf("Nothing Picked \n"); break;
		case 100: printf("New Game\n"); break;
		case 101: printf("Hall of Fame\n"); break;
		case 102: printf("Options\n"); break;
		case 103: printf("Quit\n"); break;
		default:printf("Res: %d\n", choosen);
		}
	}

	void Draw()
	{
		const float lightskycolor[] = { 0.305f, 0.305f, 0.305f, 0.0f };
		glClearBufferfv(GL_COLOR, 0, lightskycolor);

		glUseProgram(renderer->shaderProgram);
		
		for (int j = 0; j < 5; j++)
		{
			for (int i = 0; i < text[j].size; i++)
			{
				renderer->MVP = renderer->Projection * renderer->View * text[j].GetSprite()[i].GetModelMatrix();
				glUniformMatrix4fv(renderer->unfMat, 1, GL_FALSE, glm::value_ptr(renderer->MVP));
				glUniform4fv(renderer->unfColor, 1, glm::value_ptr(text[j].GetSprite()[i].GetColor()));
				glUniform4fv(renderer->unfAtlasTexcoords, 1, glm::value_ptr(text[j].GetSprite()[i].GetAtlasTexcoords()));
				text[j].GetSprite()[i].Draw();
			}
		}

		for (int i = 0; i < 4; i++)
		{
			Sprite* sprite = &button[i].GetSprite();
			renderer->MVP = renderer->Projection * renderer->View * sprite->GetModelMatrix();
			glUniformMatrix4fv(renderer->unfMat, 1, GL_FALSE, glm::value_ptr(renderer->MVP));
			glUniform4fv(renderer->unfColor, 1, glm::value_ptr(sprite->GetColor()));
			glUniform4fv(renderer->unfAtlasTexcoords, 1, glm::value_ptr(sprite->GetAtlasTexcoords()));
			sprite->Draw();
		}
		glFlush();
	}

	void DrawSelection()
	{
		const float blackcolor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		glClearBufferfv(GL_COLOR, 0, blackcolor);

		glUseProgram(renderer->selectionProgram);

		for (int i = 0; i < 4; i++)
		{
			Sprite* sprite = &button[i].GetSprite();
			renderer->MVP = renderer->Projection * renderer->View * sprite->GetModelMatrix();
			glUniformMatrix4fv(renderer->unfMatSel, 1, GL_FALSE, glm::value_ptr(renderer->MVP));
			glUniform1i(renderer->unfCode, sprite->GetId());
			sprite->Draw();
		}
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
	void Run()
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
							renderer->Resize(e.window.data1, e.window.data2);
							break;
					}
				}
			}
				
			GuiUpdate();

			switch (choosen)
			{
			case 0:
				printf("Nothing Picked \n");
				break;
			case 100:
				printf("New Game\n");
				break;
			case 101:
				printf("Hall of Fame\n");
				break;
			case 102:
				printf("Options\n");
				break;
			case 103:
				printf("Quit\n");
				quit = true;
				break;
			default:
				printf("Res: %d\n", choosen);
			}

			Draw();
		
			SDL_GL_SwapWindow(window);
		}
	}
};
#endif

