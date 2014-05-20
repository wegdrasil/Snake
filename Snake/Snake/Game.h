#ifndef SGAMEH
#define SGAMEH

#include "Renderer.h"
#include "GUI.h"
#include "Text.h"
#include "Font.h"

#include "Board.h"
#include "Mouse.h"
#include "Loser.h"
#include "Snake.h"
#include "GameLogic.h"
#include "Score.h"

class Game
{
	SDL_Window *window;
	Renderer* renderer;
	GUI gui;
	Font* font;

	Text text[2];

	unsigned int choosen;

	Board board;
	Snake snake;
	Mouse mouse;
	Loser loser;
	GameLogic logic;
	Score score;

	char lastInput;

public:
	Game();
	~Game();

	void Initialize(SDL_Window *w, Renderer* r, Font* f);

	void Reset();

	void GuiUpdate();

	void Draw();

	void DrawSelection();

	unsigned char ProcessSelection(int x, int y);
	
	Score Run(int difflevel);
	
};
#endif



