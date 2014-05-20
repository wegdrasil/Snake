#ifndef SLOSERH
#define SLOSERH

#include "Renderer.h"
#include "GUI.h"
#include "Text.h"
#include "Font.h"
#include "Textbox.h"

#include "Score.h"
#include <string>

class Loser
{
	SDL_Window *window;
	Renderer* renderer;
	GUI gui;
	Font* font;

	Text text[2];
	Textbox textbox;

	Button button;

	unsigned int choosen;
	std::string inputText;

	Score score;

public:
	Loser();
	~Loser();

	void Initialize(SDL_Window *w, Renderer* r, Font* f);

	void GuiUpdate();

	void Draw();

	void DrawSelection();

	unsigned char ProcessSelection(int x, int y);
	Score Run(int points);
};
#endif




