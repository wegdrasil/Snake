#ifndef SSCROLLBARH
#define SSCROLLBARH

#include "Button.h"

class Scrollbar
{
public:
	
	Button buttons[2];

	float sliderPosY;

	Scrollbar();
	~Scrollbar();

	void Initialize();
	void Update();

	void Scroll(float delta);
	void ScrollPlus(float delta);
	void ScrollMinus(float delta);
};
#endif

