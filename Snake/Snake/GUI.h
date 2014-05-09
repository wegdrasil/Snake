#ifndef SGUIH
#define SGUIH

#include "Button.h"
#include "Scrollbar.h"
#include "Checkbox.h"

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

	int kbditem;
	int keyentered;
	int keymod;
	int keychar;
	
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
