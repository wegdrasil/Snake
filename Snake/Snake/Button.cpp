#include "Button.h"


Button::Button()
{
	
}


Button::~Button()
{
}

void Button::Logic(GUIState* state)
{

	if (state->hot)
	{
		if (GetSprite().GetId() == state->idHot)
		{
			IfHot();
		}
	}
	else
	{
		IfInactive();
	}
	if (state->active)
	{
		if (GetSprite().GetId() == state->idActive)
		{
			IfActive();

		}
	}
}

void Button::IfHot()
{
	sprite.SetColor(sprite.GetColorHot());
	sprite.SetTexCoords(0, 478, 16, 16, 512.0f);
}

void Button::IfInactive()
{
	sprite.SetColor(sprite.GetColorInactive());
	sprite.SetTexCoords(0, 461, 16, 16, 512.0f);
}
void Button::IfActive()
{
	sprite.SetColor(sprite.GetColorActive());
	sprite.SetTexCoords(0, 495, 16, 16, 512.0f);
}