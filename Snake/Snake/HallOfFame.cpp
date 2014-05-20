#include "HallOfFame.h"


HallOfFame::HallOfFame()
{
}


HallOfFame::~HallOfFame()
{
}

void HallOfFame::Initialize(SDL_Window *w, Renderer* r, Font* f)
{
	window = w;
	renderer = r;
	font = f;

	title.SetText(font, "Hall of Fame", 700.0f, 150.0f);

	for (int i = 0; i < 11; i++)
		text[i].SetText(font, "", 700.0f, 300.0f + (i * 50));

	text[11].SetText(font, "Quit", 700.0f, 900.0f);

	Sprite* ptr = &button.GetSprite();
	ptr->UpdateModelMatrixClip(glm::vec3(650.0f, 900.0f, 0.0f), 0.0f, glm::vec3(44.0f, 44, 0.0f));
	ptr->SetTexCoords(0, 461, 16, 16, 512.0f);
	ptr->SetColorInactive(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
	ptr->SetColorActive(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	ptr->SetColorHot(glm::vec4(0.9f, 0.9f, 0.9f, 1.0f));
	ptr->SetId(100);
	ptr->Initialize();

	choosen = 0;

	for (int i = 0; i < 10; i++)
	{
		scores[i].name = "unknown";
		scores[i].points = 0;
	}
}

void HallOfFame::ReadScoresFromFile(std::string filename)
{
	std::ifstream file;
	file.open(filename);

	for (int i = 0; i < 10; i++)
	{
		char buffer[100];
		file.getline(buffer, 100);

		std::stringstream ss(buffer);

		ss >> scores[i].name;
		ss >> scores[i].points;
	}

	file.close();
}

void HallOfFame::WriteScoresToFile(std::string filename)
{
	std::ofstream file;
	file.open(filename);

	std::string line = "";

	for (int i = 0; i < 10; i++)
	{
		line += scores[i].name + " " + std::to_string(scores[i].points) + "\n";
	}

	file.write(line.c_str(), line.size());
	file.close();
}


void HallOfFame::UpdateScores()
{
	if (lastscore.points < scores[9].points)
		return;

	for (int i = 0; i < 10; i++)
	{
		//find place
		if (lastscore.points >= scores[i].points)
		{
			//move
			for (int j = 9; j > i; j--)
			{
				scores[j].name = scores[j - 1].name;
				scores[j].points = scores[j - 1].points;
			}
			//insert
			scores[i].name = lastscore.name;
			scores[i].points = lastscore.points;
			return;
		}
		else
			continue;
	}
}

void HallOfFame::GuiUpdate()
{
	button.Logic(&gui.state);
}

void HallOfFame::Draw()
{
	const float lightskycolor[] = { 0.305f, 0.305f, 0.305f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, lightskycolor);

	glUseProgram(renderer->shaderProgram);

	for (int i = 0; i < title.size; i++)
		renderer->DrawSprite(&title.GetSprite()[i]);

	for (int j = 0; j < 12; j++)
	for (int i = 0; i < text[j].size; i++)
		renderer->DrawSprite(&text[j].GetSprite()[i]);

	renderer->DrawSprite(&button.GetSprite());

	glFlush();
}

void HallOfFame::DrawSelection()
{
	const float blackcolor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, blackcolor);

	glUseProgram(renderer->selectionProgram);

	renderer->DrawSpriteSelection(&button.GetSprite());

	glFlush();
}

unsigned char HallOfFame::ProcessSelection(int x, int y)
{
	unsigned char response[4];
	GLint viewport[4];

	DrawSelection();
	DrawSelection();

	glGetIntegerv(GL_VIEWPORT, viewport);
	glReadPixels(x, viewport[3] - y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &response);

	return response[0];
}
void HallOfFame::Run(Score lastScore, bool update)
{
	bool quit = false;
	SDL_Event e;

	ReadScoresFromFile("halloffame.txt");

	lastscore = lastScore;

	if (update)
		UpdateScores();

	for (int i = 0; i < 10; i++)
		text[i].SetText(font, scores[i].name + " " + std::to_string(scores[i].points), 700.0f, 300.0f + (i * 50));
	text[10].SetText(font, scores[9].name + " " + std::to_string(scores[9].points), 700.0f, 300.0f + (9 * 50));

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_MOUSEMOTION)
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

		switch (choosen)
		{
		case 0:
			break;
		case 100:
			quit = true;
			choosen = 0;
			break;
		default:
			;
		}

		Draw();

		SDL_GL_SwapWindow(window);
	}
	WriteScoresToFile("halloffame.txt");
}