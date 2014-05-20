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
		
	void Logic(GUIState* state);

	void IfHot();
	void IfInactive();
	void IfActive();
};

#endif
