#ifndef SGUISTATEH
#define SGUISTATEH

struct GUIState
{
	int mouseX;
	int mouseY;
	int mouseXLast;
	int mouseYLast;

	bool mousedown;
	bool mousepressed;

	bool hot;
	bool active;

	unsigned char idHot;
	unsigned char idActive;

	bool idIsZero;

	int kbditem;
	int keyentered;
	int keymod;
	int keychar;

	std::string text;
	bool activeTextbox;

};
#endif