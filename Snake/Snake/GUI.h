#ifndef SGUIH
#define SGUIH

#include "Button.h"
#include "Scrollbar.h"

class GUI
{
public:
	int mouseX;
	int mouseY;
	int mouseXLast;
	int mouseYLast;

	bool mousedown;

	bool hot;
	bool active;

	unsigned char idHot;
	unsigned char idActive;
	
	Button buttons[1];
	Scrollbar scrollbar;

	float background;

	GUI();
	~GUI();

	void Initialize();
	void Update();
	void Draw();
};

#endif
