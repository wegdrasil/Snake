#ifndef SCHECKBOXH
#define SCHECKBOXH

#include "Button.h"
#include "Text.h"
#include "GUIState.h"

class Checkbox
{
	Button mButton;
	Text   mText;
	
public:
	Checkbox();
	~Checkbox();

	Sprite& GetButtonSprite() { return mButton.GetSprite(); }
	Text& GetText() { return mText; }
	Button& GetButton() { return mButton; }

	bool on;

	void Init(float x, float y, Font* font, std::string sText, int id);

	void Logic(GUIState* state);

	void IfHot();

	void IfInactive();

	void IfActive();
};

#endif