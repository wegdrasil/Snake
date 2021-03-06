#ifndef SSTARTGAMEH
#define SSTARTGAMEH

#include "Renderer.h"
#include "GUI.h"
#include "Text.h"
#include "Font.h"

#include "Options.h"
#include "Game.h"
#include "HallOfFame.h"
#include "Score.h"

class StartGame
{
	SDL_Window *window;
	Renderer* renderer;
	GUI gui;
	Font* font;

	Text text[5];
	Button button[4];

	Options options;
	Game* game;
	HallOfFame hall;
	Score lastscore;
	unsigned int choosen;
	int difflevel;

public:
	StartGame();
	~StartGame();

	void Initialize(SDL_Window *w, Renderer* r, Font* f);

	void GuiUpdate();

	void Draw();

	void DrawSelection();

	unsigned char ProcessSelection(int x, int y);
	void Run();
};
#endif

