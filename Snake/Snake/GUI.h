#ifndef SGUIH
#define SGUIH

#include "Button.h"

class GUI
{
public:
	int mouseX;
	int mouseY;
	bool mousedown;

	bool hot;
	bool active;

	unsigned char idHot;
	unsigned char idActive;
	
	Button buttons[3];

	GUI();
	~GUI();

	void Initialize();
	void Update();
	void Draw();
};

#endif
