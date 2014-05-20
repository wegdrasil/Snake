#include "GUI.h"
#include <utility>

GUI::GUI()
{
	state.mouseX = 0;
	state.mouseY = 0;
	state.mouseXLast = 0;
	state.mouseYLast = 0;
	state.mousedown = false;
	state.mousepressed = false;
	
	state.kbditem = 0;
	state.keyentered = 0;
	state.keymod = 0;
	state.keychar = 0;

	state.hot = false;
	state.active = false;
	state.idIsZero = true;

	state.text = "";
	state.activeTextbox = false;
}

GUI::~GUI()
{
}

void GUI::Initialize(Font* f)
{
}

void GUI::Update()
{
}

void GUI::Draw()
{
}