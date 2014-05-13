#ifndef SBUTTONH
#define SBUTTONH

#include "Widget.h"
#include "GUIState.h"

class Button :	public Widget
{
public:
	Button();
	~Button();
	void Initialize();
		
	void Logic(GUIState* state)
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
			IfInactive();  //bad solution :(
		}
		if (state->active)
		{
			if (GetSprite().GetId() == state->idActive)
			{
				IfActive();
				
			}
		}
	}

	void IfHot()
	{
		sprite.SetColor(sprite.GetColorHot());
		sprite.SetTexCoords(0, 478, 16, 16, 512.0f);
	}

	void IfInactive()
	{
		sprite.SetColor(sprite.GetColorInactive());
		sprite.SetTexCoords(0, 461, 16, 16, 512.0f);
	}
	void IfActive()
	{
		sprite.SetColor(sprite.GetColorActive());
		sprite.SetTexCoords(0, 495, 16, 16, 512.0f);
	}

};

#endif
