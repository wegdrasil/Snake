#ifndef SGAMELOGICH
#define SGAMELOGICH

#include "Snake.h"
#include "Mouse.h"
#include "Board.h"

struct GameLogic
{
	int points;

	GameLogic();
	~GameLogic();


	void Initialize();

	bool Run(Snake* snake, Mouse* mouse, Board* board);

	bool CheckCollisionSnakeMouse(Snake* snake, Mouse* mouse);

	bool CheckCollisionSnakeWall(Snake* snake, Board* board);

	bool CheckCollisionSnakeSnake(Snake* snake);

	int GetPoints();
};

#endif

