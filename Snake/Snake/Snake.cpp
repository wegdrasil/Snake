#include "Snake.h"

Snake::~Snake()
{
}

void Snake::Initialize(Renderer* r)
{
	renderer = r;

	switch (dificultyLevel)
	{
	case 0:
	{
			  mSnakeBody.push_back(SnakeNode(7 + 0, 5));
			  mSnakeBody.push_back(SnakeNode(5 + 0, 5));
			  mSnakeBody.push_back(SnakeNode(3 + 0, 5));
			  mSnakeBody.push_back(SnakeNode(1 + 0, 5));
			  break;
	}
	case 1:
	{
			  mSnakeBody.push_back(SnakeNode(9 + 0, 5));
			  mSnakeBody.push_back(SnakeNode(7 + 0, 5));
			  mSnakeBody.push_back(SnakeNode(5 + 0, 5));
			  mSnakeBody.push_back(SnakeNode(3 + 0, 5));
			  mSnakeBody.push_back(SnakeNode(1 + 0, 5));
			  break;
	}
	case 2:
	{
			  mSnakeBody.push_back(SnakeNode(13 + 0, 5));
			  mSnakeBody.push_back(SnakeNode(11 + 0, 5));
			  mSnakeBody.push_back(SnakeNode(9 + 0, 5));
			  mSnakeBody.push_back(SnakeNode(7 + 0, 5));
			  mSnakeBody.push_back(SnakeNode(5 + 0, 5));
			  mSnakeBody.push_back(SnakeNode(3 + 0, 5));
			  mSnakeBody.push_back(SnakeNode(1 + 0, 5));
			  break;
	}
	}
}

void Snake::Update(char input)
{

	deque.push_back(input);

	int index = mSnakeBody.size() - 1;

	for (auto object : deque)
	{
		//snake movement
		char in = object;

		if (in == 'w')
		{
			Move(index, 0, -1);
		}
		else if (in == 's')
		{
			Move(index, 0, 1);
		}
		else if (in == 'd')
		{
			Move(index, 1, 0);
		}
		else if (in == 'a')
		{
			Move(index, -1, 0);
		}
		index--;
	}


	if (deque.size() >= mSnakeBody.size())
		deque.pop_front();
}
void Snake::Move(int index, int dx, int dy)
{
	mSnakeBody.at(index).positionX += dx;
	mSnakeBody.at(index).positionY += dy;
}

void Snake::Draw()
{
	for (int i = 0; i < mSnakeBody.size(); i++)
	{
		int x = mSnakeBody.at(i).positionX;
		int y = mSnakeBody.at(i).positionY;

		Sprite sprite;
		sprite.UpdateModelMatrixClip(glm::vec3(325.0f + (x*44.0f), 100.0f + (y*44.0f), 0.0f), 0.0f, glm::vec3(44.0f, 44.0f, 0.0f));
		sprite.SetTexCoords(0, 444, 16, 16, 512.0f);
		sprite.SetColorInactive(glm::vec4(1.0f));
		sprite.Initialize();

		renderer->DrawSprite(&sprite);
	}
}