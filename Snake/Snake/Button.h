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
	}

	void IfInactive()
	{
		sprite.SetColor(sprite.GetColorInactive());
	}
	void IfActive()
	{
		sprite.SetColor(sprite.GetColorActive());
	}

};

#endif
