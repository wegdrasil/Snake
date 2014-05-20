#ifndef SHALLOFFAMEH
#define SHALLOFFAMEH

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Renderer.h"
#include "GUI.h"
#include "Text.h"
#include "Font.h"
#include "Score.h"

class HallOfFame
{
	SDL_Window* window;
	Renderer* renderer;
	Font* font;
	GUI gui;

	Text text[12];
	Text title;
	Button button;

	Score lastscore;
	Score scores[10];

	unsigned int choosen;

public:
	HallOfFame();
	~HallOfFame();

	void Initialize(SDL_Window *w, Renderer* r, Font* f);

	void ReadScoresFromFile(std::string filename);

	void WriteScoresToFile(std::string filename);


	void UpdateScores();

	void GuiUpdate();

	void Draw();

	void DrawSelection();

	unsigned char ProcessSelection(int x, int y);
	void Run(Score lastScore, bool update);
};
#endif