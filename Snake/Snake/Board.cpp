#include "Board.h"


Board::Board()
{
}


Board::~Board()
{
}

void Board::Initialize(Renderer* r)
{
	srand(time(nullptr));

	renderer = r;

	width = 20;
	height = 20;;

	startPointX = 325;
	startPointY = 100;

	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			Sprite* ptr = &board[x][y];

			ptr->UpdateModelMatrixClip(glm::vec3(325.0f + (x*44.0f), 100.0f + (y*44.0f), 0.0f), 0.0f, glm::vec3(44.0f, 44.0f, 0.0f));

			if (x == 0 && y == 0)
				ptr->SetTexCoords(381, 460, 16, 16, 512.0f);
			else if (x == 0 && y == 19)
				ptr->SetTexCoords(381, 496, 16, 16, 512.0f);
			else if (x == 19 && y == 0)
				ptr->SetTexCoords(417, 460, 16, 16, 512.0f);
			else if (x == 19 && y == 19)
				ptr->SetTexCoords(417, 496, 16, 16, 512.0f);
			else if ((x > 0 || x < 19) && y == 0)
				ptr->SetTexCoords(399, 460, 16, 16, 512.0f);
			else if ((x > 0 || x < 19) && y == 19)
				ptr->SetTexCoords(399, 496, 16, 16, 512.0f);
			else if ((y > 0 || y < 19) && x == 0)
				ptr->SetTexCoords(381, 478, 16, 16, 512.0f);
			else if ((y > 0 || y < 19) && x == 19)
				ptr->SetTexCoords(417, 478, 16, 16, 512.0f);
			else
				ptr->SetTexCoords(399, 478, 16, 16, 512.0f);

			ptr->SetColorInactive(glm::vec4(1.0f));
			ptr->Initialize();
		}

	}
}
void Board::Draw()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			renderer->DrawSprite(&board[i][j]);
		}
	}
}