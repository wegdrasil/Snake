#ifndef SSNAKEH
#define SSNAKEH

#include "Sprite.h"
#include "SnakeNode.h"
#include "Renderer.h"

#include <deque>
#include <vector>

class Snake
{
public:	
	std::deque<char> deque;
	std::vector<SnakeNode> mSnakeBody;
	Renderer* renderer;
	int dificultyLevel;

	Snake()
	{
	}

	~Snake();

	void Initialize(Renderer* r);

	void SetDificultyLevel(int level)
	{
		dificultyLevel = level;
	}

	int GetSize()
	{
		return mSnakeBody.size();
	}

	SnakeNode& GetSnakeHead()
	{
		return mSnakeBody.at(0);
	}

	void Update(char input);

	void Move(int index, int dx, int dy);
	
	void Draw();
};

#endif
