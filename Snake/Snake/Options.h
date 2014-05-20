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

	Checkbox checkbox[3];
	Text text[3];

	Button button;

	unsigned int choosen;

public:
	Options();
	~Options();

	void Initialize(SDL_Window *w, Renderer* r, Font* f);

	void GuiUpdate();

	void Draw();

	void DrawSelection();

	unsigned char ProcessSelection(int x, int y);
	int Run();
};
#endif

