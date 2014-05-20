#include "Mouse.h"


Mouse::Mouse()
{
}


Mouse::~Mouse()
{
}

void Mouse::Initialize(Renderer* r)
{
	renderer = r;
	sprite.UpdateModelMatrixClip(glm::vec3(325.0f + (positionX*44.0f), 100.0f + (positionY*44.0f), 0.0f), 0.0f, glm::vec3(44.0f, 44.0f, 0.0f));

	sprite.SetTexCoords(381, 443, 16, 16, 512.0f);
	sprite.SetColorInactive(glm::vec4(1.0f));
	sprite.Initialize();
}


void Mouse::GetNewPosition()
{
	positionX = rand() % 18 + 1;

	positionY = rand() % 18 + 1;
}

void Mouse::UpdatePosition()
{
	sprite.SetIdendityModelMatrix();
	sprite.UpdateModelMatrixClip(glm::vec3(325.0f + (positionX*44.0f), 100.0f + (positionY*44.0f), 0.0f), 0.0f, glm::vec3(44.0f, 44.0f, 0.0f));
}

void Mouse::Draw()
{
	renderer->DrawSprite(&sprite);
}