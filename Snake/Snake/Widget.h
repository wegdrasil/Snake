#ifndef SWIDGETH
#define SWIDGETH

#include "Sprite.h"

class Widget
{
protected:
	Sprite sprite;

public:
	Widget();
	~Widget();

	Sprite& GetSprite() { return sprite; };

	void Initialize();

};

#endif