#ifndef STEXTBOXH
#define STEXTBOXH

#include "Button.h"
#include "Text.h"
#include "GUIState.h"

class Textbox
{
	Button mButton;
	Text   mText;
	int mPosX, mPosY;
	bool on;
	std::string mString;
	std::string mOldString;

public:
	Textbox();
	~Textbox();

	Sprite& GetButtonSprite() { return mButton.GetSprite(); }
	Text& GetText() { return mText; }
	Button& GetButton() { return mButton; }

	void Init(float x, float y, Font* font, std::string sText, int id);

	void Logic(GUIState* state, Font* font);

	void IfHot();

	void IfInactive();

	void IfActive();
};

#endif
