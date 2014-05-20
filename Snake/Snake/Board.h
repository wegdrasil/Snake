#ifndef SBOARDH
#define SBOARDH

#include "Renderer.h"
#include "Sprite.h"

class Board
{
public:
	int width;
	int height;

	int startPointX;
	int startPointY;
	
	Renderer* renderer;

	Sprite board[20][20];

	Board();
	~Board();

	void Initialize(Renderer* r);
	void Draw();
};

#endif

