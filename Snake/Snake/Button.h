#ifndef SBUTTONH
#define SBUTTONH

#include "Widget.h"

class Button :	public Widget
{
public:
	Button();
	~Button();
	void Initialize();

	void IfHot()
	{
		sprite.SetColor(sprite.GetColorHot());
		sprite.SetTexCoords(0, 411, 13, 13, 512.0f);
	}

	void IfInactive()
	{
		sprite.SetColor(sprite.GetColorInactive());
		sprite.SetTexCoords(0, 411, 13, 13, 512.0f);
	}
	void IfActive()
	{
		sprite.SetColor(sprite.GetColorActive());
		sprite.SetTexCoords(0, 424, 13, 13, 512.0f);
	}

};

#endif
