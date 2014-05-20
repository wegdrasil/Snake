#ifndef SGUIH
#define SGUIH

#include "Button.h"
#include "Scrollbar.h"
#include "Checkbox.h"
#include "Font.h"
#include "Textbox.h"
#include "GUIState.h"

class GUI
{
public:
	GUIState state;

	GUI();
	~GUI();

	void Initialize(Font* f);
	void Update();
	void Draw();

	void ReceiveText(std::string text)
	{
		state.text = text;
	}
};

#endif
