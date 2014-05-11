#ifndef SGUIH
#define SGUIH

#include "Button.h"
#include "Scrollbar.h"
#include "Checkbox.h"
#include "Font.h"
#include "GUIState.h"

class GUI
{
public:
	GUIState state;

	Button buttons[1];
	Scrollbar scrollbar;
	Checkbox checkbox[4];
	Font* font;

	float background;

	GUI();
	~GUI();

	void Initialize(Font* f);
	void Update();
	void Draw();
};

#endif
