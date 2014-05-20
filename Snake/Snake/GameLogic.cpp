#include "GameLogic.h"


GameLogic::GameLogic()
{
}


GameLogic::~GameLogic()
{
}

void GameLogic::Initialize()
{
	points = 0;
}

bool GameLogic::Run(Snake* snake, Mouse* mouse, Board* board)
{
	if (CheckCollisionSnakeMouse(snake, mouse))
	{
		points++;
		mouse->GetNewPosition();
		mouse->UpdatePosition();
	}
	if (CheckCollisionSnakeWall(snake, board) || CheckCollisionSnakeSnake(snake))
		return false;
	return true;
}

bool GameLogic::CheckCollisionSnakeMouse(Snake* snake, Mouse* mouse)
{
	if (snake->GetSnakeHead().positionX == mouse->positionX && snake->GetSnakeHead().positionY == mouse->positionY)
		return true;
	else
		return false;
}

bool GameLogic::CheckCollisionSnakeWall(Snake* snake, Board* board)
{
	if (snake->GetSnakeHead().positionX == 0 ||
		snake->GetSnakeHead().positionX == 19 ||
		snake->GetSnakeHead().positionY == 0 ||
		snake->GetSnakeHead().positionY == 19)
	{
		return true;
	}
	else
		return  false;

}

bool GameLogic::CheckCollisionSnakeSnake(Snake* snake)
{
	for (int i = 2; i < snake->GetSize(); i++)
	if (snake->GetSnakeHead().positionX == snake->mSnakeBody.at(i).positionX && snake->GetSnakeHead().positionY == snake->mSnakeBody.at(i).positionY)
		return true;

	return false;
}

int GameLogic::GetPoints()
{
	return points;
}