#ifndef SMOUSEH
#define SMOUSEH

#include <cstdlib>
#include <ctime>

#include "Renderer.h"
#include "Sprite.h"

class Mouse
{
public:
	Mouse();
   ~Mouse();
	
	Renderer* renderer;
	Sprite sprite;

	int positionX;
	int positionY;

	void Initialize(Renderer* r);	

	void GetNewPosition();

	void UpdatePosition();

	void Draw();
};
#endif
